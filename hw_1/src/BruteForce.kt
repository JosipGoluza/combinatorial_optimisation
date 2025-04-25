import kotlin.math.max

fun calculateBruteForce(instance: Instance): Int {
    val (optimalSolutionValue, nodesVisited) = knapsackBruteForce(instance.capacity, instance.items, 0)
    return nodesVisited
}

fun knapsackBruteForce(capacity: Int, items: List<Item>, index: Int): Pair<Int, Int> {

    if (index == items.size || capacity <= 0) return Pair(0, 1)

    return if (items[index].weight > capacity) {
        val (value, nodes) = knapsackBruteForce(capacity, items, index + 1)
        Pair(value, nodes + 1)
    } else {
        val (valueWithout, nodesWithout) = knapsackBruteForce(capacity, items, index + 1)
        val (valueWith, nodesWith) = knapsackBruteForce(capacity - items[index].weight, items, index + 1)
        val bestValue = max(valueWithout, items[index].cost + valueWith)
        Pair(bestValue, nodesWithout + nodesWith + 1)
    }
}

