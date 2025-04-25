import java.io.File
import kotlin.system.measureTimeMillis

fun main() {
    val compilationTime = measureTimeMillis {
        val inputNR = readAllNRFiles(InstanceType.NR, listOfNRPairs)
        val inputZR = readAllNRFiles(InstanceType.ZR, listOfZRPairs)

        val combinedResults = goThroughFiles(inputNR) + goThroughFiles(inputZR)
        val instanceTventyResult = "a"

        createCsvAverageAndMax(combinedResults)
        createCsvForTventyInstances(combinedResults)
    }

    println("Compilation time: $compilationTime milliseconds")
}

fun createCsvForTventyInstances(combinedResults: List<Result>) {
    val header = "type,bruteForce,branchAndBound"
    val csv = combinedResults.joinToString("\n", prefix = "$header\n") { result ->
        result.instanceTwentyResults.nodesVisitedPair.joinToString("\n") { pair ->
            "${result.type},${pair.first},${pair.second}"
        }
    }
    File("src/data/resultsTwenty.csv").writeText(csv)
}

fun createCsvAverageAndMax(combinedResults: List<Result>) {
    val header = "n,type,bruteForceAverage,branchAndBoundAverage,bruteForceMax,branchAndBoundMax,totalDurationMiliSeconds"
    val csv = combinedResults.joinToString("\n", prefix = "$header\n") { result ->
        "${result.n},${result.type},${result.bruteForceAverage},${result.branchAndBoundAverage},${result.bruteForceMax},${result.branchAndBoundMax},${result.totalDuration}"
    }
    File("src/data/results.csv").writeText(csv)
}

fun goThroughFiles(input: List<InstanceSize>) = input.map { instances ->
    goThroughNExamples(instances)
}


fun goThroughNExamples(instances: InstanceSize): Result {
    val bruteForceList = mutableListOf<Int>()
    val branchAndBoundList = mutableListOf<Int>()
    val twentyNodesPair = mutableListOf<Pair<Int, Int>>()

    var totalDuration = 0.0
    instances.exampleList.map { (instance, solutionValue) ->
        val result = calculateDecisionProblems(instance)
        bruteForceList.add(result.nodesVisitedBruteForce)
        branchAndBoundList.add(result.nodesVisitedBAndB.first)
        totalDuration += result.nodesVisitedBAndB.second
        if (instance.n == 20) {
            twentyNodesPair.add(Pair(result.nodesVisitedBruteForce, result.nodesVisitedBAndB.first))
        }
    }
    return Result(
        n = instances.n,
        type = instances.type,
        bruteForceAverage = bruteForceList.average(),
        branchAndBoundAverage = branchAndBoundList.average(),
        bruteForceMax = bruteForceList.maxOrNull() ?: 0,
        branchAndBoundMax = branchAndBoundList.maxOrNull() ?: 0,
        instanceTwentyResults = InstanceTwentyResult(twentyNodesPair),
        totalDuration = totalDuration,
    )
}

fun calculateDecisionProblems(instance: Instance): NodesResult {
    val nodesVisitedBruteForce = calculateBruteForce(instance)
    val nodesVisitedBAndB = calculateBranchAndBound(instance)
    return NodesResult(nodesVisitedBruteForce, nodesVisitedBAndB)
}
