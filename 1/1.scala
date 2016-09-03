/*
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/

/*
Runtime: O(n) where n is the limit
*/

object Main {
    def main(args: Array[String]) {
        val limit = 1000
        val multiples = List(3,5)
        val answer = getSumOfMultiplesBelow(limit, multiples)
        println(answer)
    }

    def getSumOfMultiplesBelow(limit: Int, multiples: List[Int]): Int = {
        def getSum(current: Int, acc: Int): Int = current match {
            case `limit` => acc
            case _ => {
                val toAdd = if (multiples exists (num => current % num == 0)) current else 0
                getSum(current + 1, acc + toAdd)
            }
        }
        getSum(0,0)
    }
}

