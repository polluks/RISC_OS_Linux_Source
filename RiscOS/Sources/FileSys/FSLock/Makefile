# Copyright 1996 Acorn Computers Ltd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Makefile for FSLock
#

COMPONENT = FSLock
HEADER1   = FSLock
CUSTOMROM = custom

include StdTools
include AAsmModule

rom_common: ${ROM_MODULE} scrambler
	${RUN}scrambler ${ROM_MODULE}

rom: rom_common
	@${ECHO} ${COMPONENT}: rom module built & scrambled

install_rom: rom_common
	${CP} ${ROM_MODULE} ${INSTDIR}.${TARGET} ${CPFLAGS}
	${CP} ${ROM_MODULE}_gpa ${INSTDIR}.${TARGET}_gpa ${CPFLAGS}
	@${ECHO} ${COMPONENT}: rom module installed

clean::
	${XWIPE} od ${WFLAGS}
	${RM} scrambler
	${STRIPDEPEND} scrambler/mk

scrambler: scrambler.c
	${MAKE} -f scrambler/mk THROWBACK=${THROWBACK}

# Dynamic dependencies:
