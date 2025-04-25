import kotlin.math.max
import kotlin.system.measureNanoTime
import kotlin.system.measureTimeMillis
import kotlin.time.measureTime

fun calculateBranchAndBound(instance: Instance): Pair<Int, Long> {
    var totalNodesVisited: Int
    val timeTaken = measureTime {
        val (optimalSolution, nodesVisited) = knapsackBranchAndBound(
            capacity = instance.capacity,
            items = instance.items,
            index = 0,
            desiredCost = instance.minimumCost,
            currentValue = 0,
        )
        totalNodesVisited = nodesVisited
    }.inWholeMicroseconds
    return Pair(totalNodesVisited, timeTaken)
}

fun knapsackBranchAndBound(
    capacity: Int,
    items: List<Item>,
    index: Int,
    desiredCost: Int,
    currentValue: Int,
): Pair<Int, Int> {

    if (index == items.size || capacity <= 0) return Pair(0, 1)

    val upperBound = currentValue + getSumOfUndecidedItems(items, index)

    if (upperBound < desiredCost) {
        return Pair(0, 1)
    }

    return if (items[index].weight > capacity) {
        val (value, nodes) = knapsackBranchAndBound(
            capacity = capacity,
            items = items,
            index = index + 1,
            desiredCost = desiredCost,
            currentValue = currentValue,
        )
        Pair(value, nodes + 1)
    } else {
        val (valueWithout, nodesWithout) = knapsackBranchAndBound(
            capacity = capacity,
            items = items,
            index = index + 1,
            desiredCost = desiredCost,
            currentValue = currentValue,
        )
        val (valueWith, nodesWith) = knapsackBranchAndBound(
            capacity = capacity - items[index].weight,
            items = items,
            index = index + 1,
            desiredCost = desiredCost,
            currentValue = currentValue + items[index].cost,
        )
        val bestValue = max(valueWithout, items[index].cost + valueWith)
        Pair(bestValue, nodesWithout + nodesWith + 1)
    }

}

fun getSumOfUndecidedItems(items: List<Item>, index: Int): Int {
    return (index..<items.size).sumOf { currentIndex ->
        items[currentIndex].cost
    }
}
