#!/bin/bash

# Define constants and defaults
DEFAULT_FILE="IS_IS20_MC300_MW150_CWR0.8_CWCuni_GR1_bal.txt"
STATE_FILE="core_state.txt"
DEFAULT_IS=20
DEFAULT_MC=300
DEFAULT_MW=150
DEFAULT_CWR=0.8
DEFAULT_CWC="uni"
DEFAULT_GR="1" # Granularity default exponent
DEFAULT_GR_EXP="bal" # Default granularity distribution
DEFAULT_PERMUTATIONS=(1 2 3 4 5)
DEFAULT_NUM_INSTANCE=300

# Parameter arrays
N_VALUES=(10 15 20 25 30)
COST_VALUES=(25 200 400 700 1000)
WEIGHT_VALUES=(25 100 200 500 1000)
CWR_VALUES=(0.1 0.3 0.5 0.7 0.95)
CWC_VALUES=("uni" "corr" "strong")
GR_VALUES=(2 4 7 10)
GR_EXP_VALUES=("light" "heavy")

# Function to run the generator for a specific parameter set
generate_instance() {
    local n="$1"
    local mc="$2"
    local mw="$3"
    local cwr="$4"
    local cwc="$5"
    local gr="$6"
    local gr_exp="$7"
    local type="$8"

    # Construct output file name
    local file_name="${type}_IS${n}_MC${mc}_MW${mw}_CWR${cwr}_CWC${cwc}_GR${gr}_${gr_exp}.txt"

    # Run the generator
    ./kg2 -n "$n" -N "$DEFAULT_NUM_INSTANCE" -W "$mw" -C "$mc" -k "$gr" -w "$gr_exp" -c "$cwc" -R "$STATE_FILE" > "$file_name"

    echo "Generated: $file_name"
}

# Function to generate permuted instances
generate_permutations() {
    local input_file="$1"

    for perm in "${DEFAULT_PERMUTATIONS[@]}"; do
        local perm_file="PERM_IS20_MC300_MW150_CWR0.8_CWCuni_GR1_bal.txt"
        ./kg_perm -d 300 -N 5 < "$input_file" > "$perm_file"
        echo "Permuted: $perm_file"
    done
}

# generate default instance
./kg2 -n "$DEFAULT_IS" -N "$DEFAULT_NUM_INSTANCE" -W "$DEFAULT_MW" -C "$DEFAULT_MC" -k "$DEFAULT_GR" -w "$DEFAULT_GR_EXP" -c "$DEFAULT_CWC" -R "$STATE_FILE" > "$DEFAULT_FILE"

# Generate instances for each parameter
# Change `n`
#for n in "${N_VALUES[@]}"; do
#    generate_instance "$n" "$DEFAULT_MC" "$DEFAULT_MW" "$DEFAULT_CWR" "$DEFAULT_CWC" "$DEFAULT_GR" "$DEFAULT_GR_EXP" "IS"
#done

## Change `mc`
#for mc in "${COST_VALUES[@]}"; do
#    generate_instance "$DEFAULT_IS" "$mc" "$DEFAULT_MW" "$DEFAULT_CWR" "$DEFAULT_CWC" "$DEFAULT_GR" "$DEFAULT_GR_EXP" "MC"
#done
#
## Change `mw`
#for mw in "${WEIGHT_VALUES[@]}"; do
#    generate_instance "$DEFAULT_IS" "$DEFAULT_MC" "$mw" "$DEFAULT_CWR" "$DEFAULT_CWC" "$DEFAULT_GR" "$DEFAULT_GR_EXP" "MW"
#done

## Change `cwr`
#for cwr in "${CWR_VALUES[@]}"; do
#    generate_instance "$DEFAULT_IS" "$DEFAULT_MC" "$DEFAULT_MW" "$cwr" "$DEFAULT_CWC" "$DEFAULT_GR" "$DEFAULT_GR_EXP" "CWR"
#done

## Change `cwc`
#for cwc in "${CWC_VALUES[@]}"; do
#    generate_instance "$DEFAULT_IS" "$DEFAULT_MC" "$DEFAULT_MW" "$DEFAULT_CWR" "$cwc" "$DEFAULT_GR" "$DEFAULT_GR_EXP" "CWC"
#done
#
# Change `gr` and `gr_exp`
for gr in "${GR_VALUES[@]}"; do
    for gr_exp in "${GR_EXP_VALUES[@]}"; do
        generate_instance "$DEFAULT_IS" "$DEFAULT_MC" "$DEFAULT_MW" "$DEFAULT_CWR" "$DEFAULT_CWC" "$gr" "$gr_exp" "GR"
    done
done
#
## Generate permuted instances for robustness testing
#generate_permutations "$DEFAULT_FILE"

echo "All instances and permutations generated."
