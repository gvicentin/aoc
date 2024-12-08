(ns aoc.day01
  (:require
   [clojure.string :as str]
   [clojure.java.io :as io]))

(defn parse-input
  [filename]
  (let [words (-> (io/resource filename)
                  slurp
                  (str/split #"\s+"))
        nums (map Integer/parseInt words)]
    [(keep-indexed #(when (even? %1) %2) nums)
     (keep-indexed #(when (odd? %1) %2) nums)]))

(defn total-distance
  [l r]
  (reduce + (map #(abs (- %1 %2)) (sort l) (sort r))))

(defn similarity-score
  [l r]
  (reduce + (map (fn [lval] 
                 (* lval (count (filter #(= lval %) r))))
                 l)))

(let [in (parse-input "day01.in")
      l (first in)
      r (second in)]
  (println "Total distance:" (total-distance l r))
  (println "Similarity score:" (similarity-score l r)))

(comment
  (let [l [3 4 2 1 3 3]
        r [4 3 5 3 9 3]]
    (total-distance l r)
    (similarity-score l r)))
