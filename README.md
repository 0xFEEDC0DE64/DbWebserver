# DbWebserver
Custom webserver with vhosts and plugin system.

[![Build Status](https://travis-ci.org/0xFEEDC0DE64/DbWebserver.svg?branch=master)](https://travis-ci.org/0xFEEDC0DE64/DbWebserver) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/6281ee6d77e3474d8c96dffa61cec492)](https://www.codacy.com/app/0xFEEDC0DE64/DbWebserver?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=0xFEEDC0DE64/DbWebserver&amp;utm_campaign=Badge_Grade)

## Building from source
This project can only be built as part of the project structure [DbSoftware](https://github.com/0xFEEDC0DE64/DbSoftware)

```Shell
git clone https://github.com/0xFEEDC0DE64/DbSoftware.git
cd DbSoftware
git submodule update --init --recursive DbWebserver libs/DbCoreLib libs/DbNetworkLib
cd ..
mkdir build_DbSoftware
cd build_DbSoftware
qmake CONFIG+=ccache ../DbSoftware
make -j$(nproc) sub-DbWebserver
make sub-DbWebserver-install_subtargets
./bin/zeiterfassung
```
