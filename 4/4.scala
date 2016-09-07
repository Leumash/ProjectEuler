/*
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/

/*
Code Review of this problem (can use to improve answer):
http://codereview.stackexchange.com/questions/105126/project-euler-4-the-functional-way
*/

object Main {
    def main(args: Array[String]) {
        val numberOfDigits = 3
        val largestPalindrome = getLargestPalindrome(numberOfDigits)
        println(largestPalindrome)
    }

    def getLargestPalindrome(digits: Int): Int = {
        val min = (Math.pow(10, digits - 1)).toInt
        val max = (Math.pow(10, digits)).toInt
        val nums = min until max

        val palindromes = for {
            i <- nums
            j <- i until max
            candidate = i * j
            if isPalindrome(candidate.toString.toList)
        } yield candidate

        palindromes max
    }

    def isPalindrome[A](word: List[A]): Boolean = word equals word.reverse
}

