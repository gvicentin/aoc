(ns day07
  (:require [clojure.string :as str]
            [clojure.java.io :as io]))

; .......S.......
; ...............
; .......^.......
; ...............
; ......^.^......
; ...............
; .....^.^.^.....
; ...............
; ....^.^...^....
; ...............
; ...^.^...^.^...
; ...............
; ..^...^.....^..
; ...............
; .^.^.^.^.^...^.
; ...............

;; First problem
;; rays / next line splitters
;; 7 / -
;; 7 / 7
;; 6 8 / -
;; 6 8 / 6 8
;; 5 7 7 9 / -
;;
;; rays splitters -> ray' 

;; Second problem
;; Given a str line, return the starting ray position
; .......S.......
(defn ray-starting-pos [s]
  (reduce (fn [acc v] (if (= \S v) (reduced acc) (inc acc))) 0 (vec s)))

;; Third problem
;; Given a str line, return the list of splitter posisitons
;; ..^...^.....^..
(defn splitter-pos [s]
  (map first
       (filter #(= \^ (second %))
               (partition 2 (interleave (range (count s)) (vec s))))))

(defn vec-contains? [col v]
  (some? (seq (filter #(= v %) col))))

(defn step [rays splitters]
  (let [splitted (flatten (map #(if (vec-contains? splitters %)
                                  [(dec %) (inc %)]
                                  [%])
                               rays))]
    [(- (count splitted) (count rays)) (set splitted)]))

(defn solve-first [input]
  (let [si (str/split-lines input)
        sr [(ray-starting-pos (first si))]
        ss (map splitter-pos (drop 1 si))]
    (reduce (fn [{:keys [splits result]} v]
              (let [[step-splits step-result] (step result v)]
                #_(println result " / " v " -> " step-result)
                {:splits (+ splits step-splits)
                 :result step-result}))
            {:splits 0 :result sr}
            ss)))

(defn update-some [m k f]
  (if (contains? m k)
    (update m k f)
    (assoc m k 1)))

(defn step-2 [rays splitters]
  (reduce (fn [acc splitter]
            (if (contains? rays splitter)
              (-> acc
                  (update-some (dec splitter) #(+ % (get rays splitter)))
                  (update-some (inc splitter) #(+ % (get rays splitter)))
                  (update splitter (constantly 0)))
              acc))
          rays
          splitters))

(defn solve-second [input]
  (let [si (str/split-lines input)
        sr (ray-starting-pos (first si))
        ss (map splitter-pos (drop 1 si))]
    (reduce (fn [acc v]
              #_(println acc " / " v " -> " (step-2 acc v))
              (step-2 acc v))
            {sr 1}
            ss)))

(def example-input (-> "day07-example.txt"
                       io/resource
                       slurp))

(def input (-> "day07.txt"
               io/resource
               slurp))

(comment
  (solve-second example-input)

  (reduce (fn [acc [_ v]] (+ acc v))
          0
          (solve-second example-input))

  (reduce (fn [acc [_ v]] (+ acc v))
          0
          (solve-second input)))
