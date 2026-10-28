(ns day06
  (:require
   [clojure.java.io :as io]
   [clojure.string :as str]))

(defn math-resolve [col]
  (let [r (reverse col)
        op (case (first r)
             "*" *
             "+" +
             "-" -
             "/" /)]
    (apply op (map Long/parseLong (rest r)))))

(defn solve-first [input]
  (let [columns (->> input
                     str/split-lines
                     (map #(str/split (str/trim %) #"\s+")))
        size (count (first columns))]
    (->> columns
         flatten
         (map-indexed (fn [idx item] [(mod idx size) item]))
         (group-by first)
         vals
         (map #(map second %))
         (map math-resolve)
         (reduce +))))

(defn math-resolve-2 [op col]
  (let [convert (fn [col]
                  (->> col
                       (remove #(= \0 %))
                       (apply str)
                       Long/parseLong))]
    (reduce (case op
              "*" *
              "+" +
              "-" -
              "/" /)
            (case op
              "*" 1
              "+" 0
              "-" 0
              "/" 1)
            (->> col
                 (map reverse)
                 (apply interleave)
                 (partition (count col))
                 (map convert)))))

(defn solve-second [input]
  (let [operations (reverse
                    (map #(str/replace % #"," "")
                         (-> input
                             str/split-lines
                             last
                             (str/split #"\s+"))))
        read-cols (fn [line]
                    (map (fn [col] (str/replace col #"\s" "0"))
                         (str/split line #",")))
        numbers (map read-cols (-> input
                                   (str/split #"\n")
                                   drop-last))]
    (reduce + 0
            (->> numbers
                 reverse
                 (apply interleave)
                 reverse
                 (partition (count numbers))
                 (map-indexed (fn [idx item]
                                (math-resolve-2
                                 (nth operations idx) item)))))))

(def example-input
  (->> "day06-example.txt"
       io/resource
       slurp))

(def input
  (->> "day06.txt"
       io/resource
       slurp))

(comment
  (solve-first example-input)
  (solve-first input)

  (math-resolve '("123" "45" "6" "*"))
  (math-resolve '("328" "64" "98" "+"))

  (math-resolve-2 "+" '("640" "230" "314"))
  (math-resolve-2 "*" '("051" "387" "215"))
  (math-resolve-2 "+" '("328" "640" "980"))
  (math-resolve-2 "*" '("123" "045" "006"))

  (solve-second example-input)
  (solve-second input))
