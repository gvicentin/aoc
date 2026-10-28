(ns day05
  (:require
   [clojure.string :as str]
   [clojure.java.io :as io]))

;; Example

; 3-5
; 10-14
; 16-20
; 12-18
;
; 1
; 5
; 8
; 11
; 17
; 32

(def ranges [[3 5] [10 14] [16 20] [12 18]])

(def ids [1 5 8 11 17 32])

(defn fresh? [id ranges]
  (some true? (map (fn [[s e]] (and (>= id s) (<= id e))) ranges)))

(defn solve-first [input]
  (let [ranges (->> input
                    (take-while (complement empty?))
                    (map #(let [[s e] (str/split % #"-")]
                            [(Long/parseLong s) (Long/parseLong e)])))
        ids (->> input
                 (drop-while #(or (empty? %) (re-find #"-" %)))
                 (map Long/parseLong))]
    (->> ids
         (filter #(fresh? % ranges))
         count)))

(def example-input (-> "day05-example.txt"
                       io/resource
                       slurp
                       str/split-lines))

(def example-ranges (->> example-input
                         (take-while (complement empty?))
                         (map #(let [[s e] (str/split % #"-")]
                                 [(Long/parseLong s) (Long/parseLong e)]))))

(defn prune-ranges
  ([ranges]
   (prune-ranges [] (first ranges) (rest ranges)))
  ([acc head tail]
   (if (seq tail)
     (let [[sh eh] head
           [st et] (first tail)]
       (if (< eh st)
         (recur (conj acc head) (first tail) (rest tail))
         (recur acc [sh (max eh et)] (rest tail))))
     (conj acc head))))

(def input (-> "day05.txt"
               io/resource
               slurp
               str/split-lines))

(def ranges (->> input
                 (take-while (complement empty?))
                 (map #(let [[s e] (str/split % #"-")]
                         [(Long/parseLong s) (Long/parseLong e)]))))

(comment
  (prune-ranges (sort-by first example-ranges))

  (last (sort-by first ranges))
  (->> (sort-by first ranges)
       (map (fn [[s e]] (format "%15d - %15d" s e)))
       (str/join "\n")
       (spit "output.txt"))

  (->> (sort-by first ranges)
       prune-ranges
       (map (fn [[s e]] (format "%15d - %15d" s e)))
       (str/join "\n")
       (spit "output-prune.txt"))

  (reduce (fn [accum [s e]]
            (+ accum (inc (- e s))))
          0
          (prune-ranges (sort-by first example-ranges)))

  (reduce (fn [accum [s e]]
            (+ accum (inc (- e s))))
          0
          (prune-ranges (sort-by first ranges))))

