# Progress

## Programs

| Version | Program | Functions | Matched | Code | .data | .rodata |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| 7.1 | as0 | 152 | 150 | 92.71% | 100.00% | 100.00% |
| 7.1 | as1 | 523 | 104 | 21.33% | 3.35% | 28.99% |
| 7.1 | cc | 64 | 64 | 100.00% | 100.00% | 100.00% |
| 7.1 | cfe | 431 | 109 | 29.34% | 79.35% | 48.02% |
| 7.1 | ugen | 465 | 465 | 100.00% | 100.00% | 100.00% |
| 7.1 | umerge | 66 | 0 | 0.00% | 0.00% | 0.00% |
| 7.1 | uopt | 521 | 0 | 0.00% | 0.00% | 0.00% |
| 7.1 | **subtotal** | 2222 | 892 | 39.65% | 59.84% | 57.84% |
| 5.3 | as0 | 151 | 150 | 96.85% | 100.00% | 100.00% |
| 5.3 | cc | 59 | 1 | 0.01% | 72.09% | 23.73% |
| 5.3 | cfe | 432 | 0 | 0.00% | 0.00% | 0.00% |
| 5.3 | ugen | 471 | 0 | 0.00% | 0.00% | 0.00% |
| 5.3 | **subtotal** | 1113 | 151 | 6.39% | 8.82% | 15.50% |
| **all** | **all programs** | 3335 | 1043 | 27.96% | 39.53% | 41.22% |

## Libraries

| Version | Library | Functions | Matched | Code | .data | .rodata |
| --- | --- | ---: | ---: | ---: | ---: | ---: |
| 7.1 | libc | 1 | 0 | 0.00% | 0.00% | 0.00% |
| 7.1 | libelf | 182 | 0 | 0.00% | 0.00% | 0.00% |
| 7.1 | libfe | 12 | 0 | 0.00% | 0.00% | 0.00% |
| 7.1 | libmdebug | 21 | 0 | 0.00% | 0.00% | 0.00% |
| 7.1 | libmisc | 13 | 0 | 0.00% | 0.00% | 0.00% |
| 7.1 | libmld | 709 | 7 | 0.13% | 0.00% | 0.00% |
| 7.1 | libp | 149 | 28 | 9.44% | 0.00% | 8.25% |
| 7.1 | libu | 78 | 74 | 98.58% | 98.12% | 99.77% |
| 7.1 | libxmalloc | 50 | 0 | 0.00% | 0.00% | 0.00% |
| 7.1 | **subtotal** | 1215 | 109 | 16.00% | 1.80% | 6.85% |
| 5.3 | libc | 1 | 0 | 0.00% | 0.00% | 0.00% |
| 5.3 | libfe | 12 | 0 | 0.00% | 0.00% | 0.00% |
| 5.3 | libmdebug | 7 | 0 | 0.00% | 0.00% | 0.00% |
| 5.3 | libmld | 355 | 0 | 0.00% | 0.00% | 0.00% |
| 5.3 | libp | 43 | 0 | 0.00% | 0.00% | 6.44% |
| 5.3 | libu | 32 | 4 | 0.36% | 98.12% | 99.80% |
| 5.3 | libxmalloc | 24 | 0 | 0.00% | 0.00% | 0.00% |
| 5.3 | **subtotal** | 474 | 4 | 0.05% | 2.20% | 5.75% |
| **all** | **all libraries** | 1689 | 113 | 11.59% | 1.91% | 6.52% |

## Total

| Scope | Functions | Matched | Code | .data | .rodata |
| --- | ---: | ---: | ---: | ---: | ---: |
| Programs | 3335 | 1043 | 27.96% | 39.53% | 41.22% |
| Libraries | 1689 | 113 | 11.59% | 1.91% | 6.52% |
| **All** | 5024 | 1156 | 24.25% | 34.57% | 35.72% |

Percentages are matched byte percentages.

Only programs with a generated disassembly (`.disasm` stamp) are included. Library rows are statically linked library code found in target objects. They are counted separately from the program that embeds them; library splits are named `library/member`.
