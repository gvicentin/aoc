(ns day01
  "https://adventofcode.com/2025/day/1"
  (:require
   [clojure.java.io :as io]
   [clojure.string :as str]))

;; L -> -num
;; R -> +num
;; target -> current + ammount

(def starting 50)
(def size 100)

(defn solve-first [rotations]
  (reduce
   (fn [{c :cur p :pass} a]
     (let [nc (mod (+ c a) size)]
       {:cur nc
        :pass (if (= 0 nc) (inc p) p)}))
   {:cur starting
    :pass 0}
   rotations))

(defn- floor-div [a b] (Math/floorDiv (long a) (long b)))

(defn solve-second [rotations]
  (reduce
   (fn [{c :cur p :pass} a]
     (let [nc (+ c a)
           crossings (if (pos? a)
                       (- (floor-div nc size) (floor-div c size))
                       (- (floor-div (dec c) size) (floor-div (dec nc) size)))]
       {:cur (mod nc size)
        :pass (+ p crossings)}))
   {:cur starting
    :pass 0}
   rotations))

(defn- parse-line [line]
  (* (if (= \L (first line)) -1 1)
     (Integer/parseInt (apply str (rest line)))))

(defn parse-input [input]
  (->> input
       str/split-lines
       (map parse-line)))

(def example [-68000 -30 48 -5 60 -55 -1 -99 14 -82])

(comment
  (solve-first [-68 -30 48 -5 60 -55 -1 -99 14 -82])

  (solve-second [-68 -30 48 -5 60 -55 -1 -99 14 -82])
  (solve-second [50 1 -1])

  (parse-input "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82")

  (-> "day01.txt"
      io/resource
      slurp
      parse-input
      solve-first)

  (-> "day01.txt"
      io/resource
      slurp
      parse-input
      solve-second))
