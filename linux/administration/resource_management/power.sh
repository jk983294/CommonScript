# control power by using idling power states (C-states), changing CPU frequency (P-states), and throttling the CPU (T-states)

# C-states reflect the capability of an idle processor to turn off unused components to save power
# The higher the C number, the deeper the CPU sleep mode, (C0 - C3)
man cpupower-idle-set

# processor can be in one of several CPU performance states (P-states)
# P-states are operational states that relate to CPU frequency and voltage
# To operate at any P-state, the processor must be in the C0 state
# The higher the P-state, the lower the frequency and voltage at which the processor runs, (P0 - P3)

cpupower frequency-info                 # shows the statistics of the cpufreq driver
cpupower idle-info                      # shows the statistics of the cpuidle driver
cpupower idle-set -d 5                  # disable the deepest sleep state
cpupower monitor                        # monitor

cpupower frequency-set -g performance   # activate the performance governor