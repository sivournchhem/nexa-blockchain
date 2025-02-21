AUTOMAKE_OPTIONS = foreign subdir-objects

bin_PROGRAMS = nexad nexa-cli

nexad_SOURCES = \
    main.cpp \
    network/network.cpp \
    consensus/consensus.cpp \
    mempool/mempool.cpp \
    governance/governance.cpp  # ✅ Ensure this is included

nexa_cli_SOURCES = \
    rpc/nexa-cli.cpp
nexad_LDADD = governance/governance.o
