(ns aoc.day03
  (:require
   [clojure.java.io :as io]))

(def mul-pattern #"mul\((\d{1,3}),(\d{1,3})\)")
(def do-pattern #"mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\)")

(defn add-mul [s]
  (->> s
       (re-seq mul-pattern)
       (map rest)
       (map #(map Integer/parseInt %))
       (reduce (fn [acc [v1 v2]] (+ acc (* v1 v2))) 0)))

(defn add-mul-with-do [s]
  (loop [acc 0
         enabled true
         groups (re-seq do-pattern s)]
    (let [group (first groups)
          gt (first group)
          v1 (second group)
          v2 (nth group 2)]
      (if (empty? groups)
        acc
        (recur
         (if (or (false? enabled) (= gt "do()") (= gt "don't()"))
           acc
           (+ acc (* (Integer/parseInt v1) (Integer/parseInt v2))))
         (cond
           (= gt "do()") true
           (= gt "don't()") false
           :else enabled)
         (rest groups))))))

(let [s (slurp (io/resource "day03.in"))]
  (println "Mul:" (add-mul s))
  (println "Mul with do:" (add-mul-with-do s)))

(comment
  (add-mul "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))")
  (add-mul-with-do "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"))
