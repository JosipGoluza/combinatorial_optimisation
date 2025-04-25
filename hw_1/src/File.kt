import java.io.File

val listOfNRPairs = listOf(
    Pair("NR4_inst.dat", "NK4_sol.dat"),
    Pair("NR10_inst.dat", "NK10_sol.dat"),
    Pair("NR15_inst.dat", "NK15_sol.dat"),
    Pair("NR20_inst.dat", "NK20_sol.dat"),
//Pair("NR22_inst.dat", "NK22_sol.dat"),
//    Pair("NR25_inst.dat", "NK25_sol.dat"),
//    Pair("NR27_inst.dat", "NK27_sol.dat"),
//    Pair("NR30_inst.dat", "NK30_sol.dat"),
//    Pair("NR32_inst.dat", "NK32_sol.dat"),
//    Pair("NR35_inst.dat", "NK35_sol.dat"),
//    Pair("NR37_inst.dat", "NK37_sol.dat"),
//    Pair("NR40_inst.dat", "NK40_sol.dat")
)

val listOfZRPairs = listOf(
    Pair("ZR4_inst.dat", "ZK4_sol.dat"),
    Pair("ZR10_inst.dat", "ZK10_sol.dat"),
    Pair("ZR15_inst.dat", "ZK15_sol.dat"),
    Pair("ZR20_inst.dat", "ZK20_sol.dat"),
// Pair("ZR22_inst.dat", "ZK22_sol.dat"),
//    Pair("ZR25_inst.dat", "ZK25_sol.dat"),
//    Pair("ZR27_inst.dat", "ZK27_sol.dat"),
//    Pair("ZR30_inst.dat", "ZK30_sol.dat"),
//    Pair("ZR32_inst.dat", "ZK32_sol.dat"),
//    Pair("ZR35_inst.dat", "ZK35_sol.dat"),
//    Pair("ZR37_inst.dat", "ZK37_sol.dat"),
//    Pair("ZR40_inst.dat", "ZK40_sol.dat")
)


fun readAllNRFiles(directory: InstanceType, pairList:  List<Pair<String, String>>): List<InstanceSize> {
    return pairList.map { (instance, solution) ->
        val instanceContent = File("src/data/$directory/$instance").bufferedReader().use { it.readText() }
        val solutionContent = File("src/data/$directory/$solution").bufferedReader().use { it.readText() }
        val exampleList = parseFromFile(instanceContent, solutionContent)
        InstanceSize(getNFromDirectory(instance), directory, exampleList)
    }
}

fun getNFromDirectory(instance: String): Int {
    return instance.substring(2, instance.indexOf('_')).toInt()
}

fun parseFromFile(instanceContent: String, solutionContent: String): List<Example> {
    val instances = instanceContent.lines().dropLast(1)
    val solutions = solutionContent.lines().dropLast(1)
    return instances.mapIndexed { index, instance ->
        val instanceValues = instance.split(" ")
        val n = instanceValues[1].toInt()
        val capacity = instanceValues[2].toInt()
        val minimumCost = instanceValues[3].toInt()
        val items = instanceValues.drop(4).chunked(2).map { (weight, cost) ->
            Item(weight.toInt(), cost.toInt())
        }
        val solution = solutions[index].split(" ")[2].toInt()
        Example(Instance(n, capacity, minimumCost, items), solution)
    }
}
