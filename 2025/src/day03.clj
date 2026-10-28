(ns day03
  (:require
   [clojure.string :as str]
   [clojure.java.io :as io]))

; 987654321111111
; 811111111111119
; 234234234234278
; 818181911112111

(defn max-joltage [bank]
  (let [parsed (map #(Integer/parseInt (str %)) (vec bank))
        but-last (pop (into [] parsed))
        fg (reduce-kv
            (fn [{amax :max :as a} ci cv]
              (if (> cv amax) {:i ci :max cv} a))
            {:i 0 :max 0}
            but-last)
        dropped (drop (inc (:i fg)) parsed)
        sg (reduce #(if (> %1 %2) %1 %2) dropped)]
    (Long/parseLong (str (:max fg) sg))))

(defn solve-first [banks]
  (->> banks
       str/split-lines
       (map max-joltage)
       (reduce +)))

(defn solve-second*
  ([bank]
   (solve-second* [] (map #(Integer/parseInt (str %)) (vec bank)) 11))
  ([accum bank d]
   (if (>= d 0)
     (let [r (take (- (count bank) d) bank)
           g (reduce-kv
              (fn [{amax :max :as a} ci cv]
                (if (> cv amax) {:i ci :max cv} a))
              {:i 0 :max 0}
              (vec r))]
       (solve-second* (conj accum (:max g)) (drop (inc (:i g)) bank) (dec d)))
     (apply str accum))))

(defn solve-second [banks]
  (->> banks
       str/split-lines
       (map solve-second*)
       (map Long/parseLong)
       (reduce +)))

(comment
  (solve-second* [] (map #(Integer/parseInt (str %)) (vec "987654321111111")) 11)

  (solve-second "987654321111111")
  (solve-second "811111111111119")
  (solve-second "234234234234278")
  (solve-second "818181911112111")

  (take (dec (count [1 2 3])) [1 2 3])

  (pop (into [] (map #(Integer/parseInt (str %)) (vec "9811"))))

  (reduce #(if (> %1 %2) %1 %2)
          {:i 0 :max 0} [8 8 11 10])

  (reduce-kv
   (fn [{amax :max :as a} ci cv]
     (if (> cv amax) {:i ci :max cv} a))
   {:i -1 :max -1}
   [1 2 3 4])

  (max-joltage "987654321111111")
  (max-joltage "811111111111119")
  (max-joltage "234234234234278")
  (max-joltage "818181911112111")

  (-> "day03.txt"
      io/resource
      slurp
      solve-first)

  (-> "day03-example.txt"
      io/resource
      slurp
      str/trim-newline
      solve-second)

  (-> "day03.txt"
      io/resource
      slurp
      str/trim-newline
      solve-second))
