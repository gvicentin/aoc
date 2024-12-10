(ns aoc.day02
  (:require
   [clojure.string :as str]
   [clojure.java.io :as io]))

(defn parse-input
  [filename]
  (->> (io/resource filename)
       slurp
       str/split-lines
       (map #(str/split % #"\s+"))
       (map #(vec (map Integer/parseInt %)))))

(defn safe?
  [coll]
  (let [asc (apply > coll)
        des (apply < coll)
        d (map #(abs (apply - %)) (partition 2 1 coll))
        dmin (apply min d)
        dmax (apply max d)]
    (and
     (or asc des)
     (and (>= dmin 1) (<= dmax 3)))))

(defn safe-dampener?
  [coll]
  (if (safe? coll)
    true
    (loop [idx 0 lcoll coll]
      (cond
        (>= idx (count coll)) false
        (safe? (into (subvec coll 0 idx) (subvec coll (inc idx)))) true
        :else (recur (inc idx) (rest lcoll))))))

(defn count-safe
  [coll safe-fn?]
  (->> coll
       (map safe-fn?)
       (filter true?)
       count))

(let [in (parse-input "day02.in")]
  (println "Safe count" (count-safe in safe?))
  (println "Safe dampener count" (count-safe in safe-dampener?)))

(comment
  (let [a [[7 6 4 2 1]
           [1 2 7 8 9]
           [9 7 6 2 1]
           [1 3 2 4 5]
           [8 6 4 4 1]
           [1 3 6 7 9]]]
    (count-safe a safe?)
    (count-safe a safe-dampener?)))
