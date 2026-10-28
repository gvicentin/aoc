(ns day04
  (:require
   [clojure.java.io :as io]
   [clojure.string :as str]))

; Example Input
;
; ..@@.@@@@.
; @@@.@.@.@@
; @@@@@.@.@@
; @.@@@@..@.
; @@.@@@@.@@
; .@@@@@@@.@
; .@.@.@.@@@
; @.@@@.@@@@
; .@@@@@@@@.
; @.@.@@@.@.

; Forklifts can access the following rolls ('X')
;
; ..xx.xx@x.
; x@@.@.@.@@
; @@@@@.x.@@
; @.@@@@..@.
; x@.@@@@.@x
; .@@@@@@@.@
; .@.@.@.@@@
; x.@@@.@@@@
; .@@@@@@@@.
; x.x.@@@.x.

(def example-input "..@@.@@@@.@@@.@.@.@@@@@@@.@.@@@.@@@@..@.@@.@@@@.@@.@@@@@@@.@.@.@.@.@@@@.@@@.@@@@.@@@@@@@@.@.@.@@@.@.")

(defn adjacents [idx sa sl]
  (remove #(or (< % 0)
               (>= % (* sa sl))
               (and (= (mod idx sa) 0) (= (mod % sa) (dec sa)))
               (and (= (mod idx sa) (dec sa)) (= (mod % sa) 0)))
          [(- idx sa)
           (inc (- idx sa))
           (inc idx)
           (inc (+ idx sa))
           (+ idx sa)
           (dec (+ idx sa))
           (dec idx)
           (dec (- idx sa))]))

(defn count-rolls [input idx slots-across slot-lines]
  (reduce (fn [acc adj]
            (if (= \@ (nth input adj)) (inc acc) acc))
          0
          (adjacents idx slots-across slot-lines)))

(defn set-char-at [^String s idx ^Character ch]
  (str (doto (StringBuilder. s) (.setCharAt idx ch))))

(defn solve-first
  ([input slots-across slot-lines]
   (solve-first 0 input slots-across slot-lines))
  ([accum input slots-across slot-lines]
   (let [rolls (->> (range (count input))
                    (filter #(= \@ (nth input %)))
                    (map (fn [idx] [idx (count-rolls input idx slots-across slot-lines)])))
         to-remove (filter (fn [[_ count]] (< count 4)) rolls)
         new-input (reduce (fn [acc [idx _]] (set-char-at acc idx \.)) input to-remove)]
     (if (empty? to-remove)
       accum
       (recur (+ accum (count to-remove)) new-input slots-across slot-lines)))))

(comment
  (let [content (-> "day04-example.txt"
                    io/resource
                    slurp
                    str/trim-newline)
        splitted (str/split-lines content)
        slots-across (count (first splitted))
        slots-lines (count splitted)]
    (solve-first (str/replace content #"\n" "")
                 slots-across
                 slots-lines))

  (let [content (-> "day04.txt"
                    io/resource
                    slurp
                    str/trim-newline)
        splitted (str/split-lines content)
        slots-across (count (first splitted))
        slots-lines (count splitted)]
    (solve-first (str/replace content #"\n" "")
                 slots-across
                 slots-lines)))
