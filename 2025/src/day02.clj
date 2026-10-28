(ns day02
  (:require
   [clojure.java.io :as io]
   [clojure.string :as str]))

; 11-22,95-115,998-1012,1188511880-1188511890,222220-222224,
; 1698522-1698528,446443-446449,38593856-38593862,565653-565659,
; 824824821-824824827,2121212118-2121212124

;; 2 digit num
;; 11 - 1 digit 2x

;; 3 digit num
;; 999 - 1 digit 3x

;; 4 digit num
;; 9999 - 1 digit 4x
;; 9090 - 2 digit 2x

;; 5 digit num
;; 99999 - 1 digit 5x

;; 6 digit num
;; 999999 - 1 digit 6x
;; 909090 - 2 digit 3x
;; 123123 - 3 digit 2x

(defn- divs [ndigits]
  (filter #(= 0 (mod ndigits %)) (range 1 ndigits)))

(def divs-memo (memoize divs))

(defn- split-digits [id]
  (map (fn [d]
         (map (fn [dr]
                (subs id (* dr d) (+ d (* dr d))))
              (range (/ (count id) d))))
       (divs-memo (count id))))

(def split-sigits-memo (memoize split-digits))

(defn- invalid? [id]
  (some #(apply = %) (split-sigits-memo id)))

(defn- solve-second [id-ranges]
  (reduce +
          (flatten (map (fn [id-range]
                          (let [[s e] (str/split id-range #"-")]
                            (filter #(invalid? (str %))
                                    (range (Long/parseLong s)
                                           (inc (Long/parseLong e))))))
                        id-ranges))))

(comment
  (apply = ["1" "1" "1" "1"])

  (divs (count "123123"))
  (divs (count "111"))

  (some #(apply = %) (split-digits "123123"))
  (some #(apply = %) (split-digits "11"))
  (some #(apply = %) (split-digits "21212121"))

  (filter #(invalid? (str %)) (range 95 (inc 115)))

  (def example
    ["11-22" "95-115" "998-1012" "1188511880-1188511890" "222220-222224"
     "1698522-1698528" "446443-446449" "38593856-38593862" "565653-565659"
     "824824821-824824827" "2121212118-2121212124"])

  (solve-second example)

  (-> "day02-example.txt"
      io/resource
      slurp
      str/trim-newline
      (str/split #",")
      solve-second)

  (-> "day-02.txt"
      io/resource
      slurp
      str/trim-newline
      (str/split #",")
      solve-second))
