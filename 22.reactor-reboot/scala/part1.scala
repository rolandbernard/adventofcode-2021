
import scala.io.StdIn
import scala.collection.mutable.ListBuffer
import scala.collection.mutable.HashMap
import scala.collection.mutable.HashSet

type Box = ((Int, Int), (Int, Int), (Int, Int))

object part1 {
    def main(args: Array[String]) = {
        var seq = ListBuffer[(Boolean, Box)]()
        var line = ""
        while ({line = StdIn.readLine(); line != null}) {
            var split = line.split(" ")
            var on = split(0) == "on"
            var arr = split(1).split(",").map(s => s.split("=")(1).split("\\.\\.").map(v => v.toInt))
            var box = ((arr(0)(0), arr(0)(1)), (arr(1)(0), arr(1)(1)), (arr(2)(0), arr(2)(1)))
            if (box(0)(0).min(box(1)(0)).min(box(2)(0)) >= -50 && box(0)(1).max(box(1)(1)).max(box(2)(1)) <= 50) {
                seq += ((on, box))
            }
        }
        var reactor = HashMap[Box, Int]().withDefaultValue(0)
        for ((on, bx) <- seq) {
            var todelete = HashSet[Box]()
            var updates = HashMap[Box, Int]().withDefaultValue(0)
            for ((xb, sgn) <- reactor) {
                var isx0 = bx(0)(0).max(xb(0)(0)); var isx1 = bx(0)(1).min(xb(0)(1))
                var isy0 = bx(1)(0).max(xb(1)(0)); var isy1 = bx(1)(1).min(xb(1)(1))
                var isz0 = bx(2)(0).max(xb(2)(0)); var isz1 = bx(2)(1).min(xb(2)(1))
                var box = ((isx0, isx1), (isy0, isy1), (isz0, isz1))
                if (xb == box) {
                    todelete += box
                } else if (isx0 <= isx1 && isy0 <= isy1 && isz0 <= isz1) {
                    updates(box) -= sgn
                }
            }
            for (xb <- todelete) {
                reactor -= xb
            }
            for ((xb, sgn) <- updates) {
                reactor(xb) += sgn
                if (reactor(xb) == 0) {
                    reactor -= xb
                }
            }
            if (on) {
                reactor(bx) += 1
            }
        }
        var sum = 0
        for ((xb, sgn) <- reactor) {
            sum += sgn * (xb(0)(1) - xb(0)(0) + 1) * (xb(1)(1) - xb(1)(0) + 1) * (xb(2)(1) - xb(2)(0) + 1)
        }
        println("Result: " + sum)
    }
}

