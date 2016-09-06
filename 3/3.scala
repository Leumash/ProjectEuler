/*
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/

import scala.annotation.tailrec
import scala.collection.parallel.mutable
import scala.compat.Platform

object Main {
    def main(args: Array[String]) {
        val num:Long = 600851475143L

        val answer = getLargestPrimeFactor(num)

        println(answer)
    }

    def getLargestPrimeFactor(limit: Long): Long = {
        val primes = sieveOfEratosthenes(Math.sqrt(limit).toInt)

        val primeFactors = for {
            prime <- primes
            if limit % prime == 0
        } yield prime

        primeFactors max
    }

    // From https://rosettacode.org/wiki/Sieve_of_Eratosthenes
    def sieveOfEratosthenes(limit: Int) = {
        val (primes: mutable.ParSet[Int], sqrtLimit) = (mutable.ParSet.empty ++ (2 to limit), limit)
        @tailrec
        def prim(candidate: Int): Unit = {
            if (candidate <= sqrtLimit) {
                if (primes contains candidate) primes --= candidate * candidate to limit by candidate
                prim(candidate + 1)
            }
        }
        prim(2)
        primes
    }
}

