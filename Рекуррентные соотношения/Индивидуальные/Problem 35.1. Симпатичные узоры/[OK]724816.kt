import java.io.FileReader
import java.io.FileWriter
import java.math.BigInteger
import kotlin.system.exitProcess

var m = 0
var n = 0
var bound = 0
var answer : BigInteger = BigInteger.valueOf(0)
var acceptedArr = Array<Array<BigInteger>>(1, fun (_:Int):Array<BigInteger> {return Array<BigInteger>(1,
    fun(_:Int):BigInteger {return BigInteger.valueOf(0);})});
var interactions = ArrayList<ArrayList<Boolean>>()

fun main() {
        readFile()
        checkEdgeCases()
        bound = 1 shl m;
        acceptedArr = Array<Array<BigInteger>>(n, fun (_: Int):Array<BigInteger> {return Array<BigInteger>(bound,
            fun(_: Int):BigInteger {return BigInteger.valueOf(0)})} )
        interactions = ArrayList<ArrayList<Boolean>>(bound);
        createInteractionsMatrix()

        if (n == 2) {
            for (item in acceptedArr[0]) {
                answer = answer.add(item)
            }
            writeToFile()
        }

        for (i in 1 until n - 1){
            for (a in 0 until bound){
                if (acceptedArr[i-1][a] == BigInteger.valueOf(0)){
                    continue
                }
                var b = 0;
                while (b < bound){
                    if (interactions[a][b])
                    acceptedArr[i][b] = acceptedArr[i][b].add(acceptedArr[i-1][a])
                    b++
                }
            }
        }
        for (item in acceptedArr[n - 2]){
            answer = answer.add(item)
        }

        writeToFile()
}

fun createInteractionsMatrix(){
    var a = 0; var b = 0
    while (a < bound) {
        val temp = ArrayList<Boolean>()
        while (b < bound){
            if (compare(a, b)){
                acceptedArr[0][b] = acceptedArr[0][b].add(BigInteger.valueOf(1));
                temp.add(true)
            }
            else{
                temp.add(false)
            }
            b++
        }
        interactions.add(temp)
        b = 0
        a++
    }
}

fun isAttractive(a1: Boolean, a2: Boolean, b1: Boolean, b2: Boolean): Boolean {
    val a = (if (a1) 1 else 0) + (if(a2) 1 else 0) + (if(b1) 1 else 0) + (if(b2) 1 else 0)
    return a != 4 && a != 0
}

fun compare(aIn: Int, bIn: Int): Boolean {
    if (aIn > bIn){
        return interactions[bIn][aIn]
    }
    var counter = m
    var a = aIn
    var b = bIn
    while(counter > 1){
        val attractive = isAttractive(
            a.mod(2) == 0, (a shr 1).mod(2) == 0, b.mod(2) == 0,
            (b shr 1).mod(2) == 0
        )
        if (!attractive){
            return false
        }
        a = (a shr 1)
        b = (b shr 1)
        counter--
    }
    return true
}

fun checkEdgeCases(){
    if (m == 1 && n == 1){
        answer = BigInteger.valueOf(2)
        writeToFile()
    }
    if (m == 1){
        answer = (1 shl n).toBigInteger()
        writeToFile()
    }
    if (n == 1){
        answer = (1 shl m).toBigInteger()
        writeToFile()
    }
}

fun readFile(){

    val fileReader = FileReader("in.txt")
    val lines = fileReader.readLines()
    m = lines[0].toInt()
    n = lines[1].toInt()
    fileReader.close()
}

fun writeToFile(){
    val fileWriter = FileWriter("out.txt")
    fileWriter.write(answer.toString())
    fileWriter.close()
    exitProcess(0)
}