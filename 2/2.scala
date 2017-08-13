/*
Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will be:

1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
*/

object Main {
    def main(args: Array[String]) {
        val limit = 4000000
        val sumOfEvenNumberedFibonacciNumbers = getSumOfEvenNumberedFibonacciNumbers(limit)

        println(sumOfEvenNumberedFibonacciNumbers)
    }

    def getSumOfEvenNumberedFibonacciNumbers(limit: Int): Int = {
        def isEven = (num: Int) => num % 2 == 0
        def getFibonacciNumbers(fibs: List[Int]): List[Int] = fibs match {
            case Nil => getFibonacciNumbers(1 :: fibs)
            case _ :: Nil => getFibonacciNumbers(1 :: fibs)
            case head :: tail if (head >= limit) => fibs
            case a :: b :: tail => getFibonacciNumbers(a + b :: fibs)
        }
        val fibonacciNumbers = getFibonacciNumbers(Nil)
        fibonacciNumbers filter isEven sum
    }
}
