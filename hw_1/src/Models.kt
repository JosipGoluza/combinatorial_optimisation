data class Item(
    val weight: Int,
    val cost: Int
)

data class Instance(
    val n: Int,
    val capacity: Int,
    val minimumCost: Int,
    val items: List<Item>,
)

data class Example(
    val instance: Instance,
    val solutionValue: Int
)

enum class InstanceType(val type: String) {
    NR("NR"),
    ZR("ZR")
}

data class InstanceSize(
    val n: Int,
    val type: InstanceType,
    val exampleList: List<Example>
)

data class NodesResult(
    val nodesVisitedBruteForce: Int,
    val nodesVisitedBAndB: Pair<Int,Long>,
)

data class InstanceTwentyResult(
    val nodesVisitedPair: List<Pair<Int,Int>>,
)

data class Result(
    val n: Int,
    val type: InstanceType,
    val bruteForceAverage: Double,
    val branchAndBoundAverage: Double,
    val bruteForceMax: Int,
    val branchAndBoundMax: Int,
    val instanceTwentyResults: InstanceTwentyResult,
    val totalDuration: Double,
)