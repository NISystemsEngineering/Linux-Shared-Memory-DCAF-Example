<?xml version="1.0"?>
<?CDF VERSION="5.0"?>
<DEFINITION>
<SOFTPKG NAME="{14D73D78-4CB7-48BC-B561-34366735187B}" VERSION="1.0.0.3" TYPE="STARTUP">
	<TITLE>Linux Shared Memory and DCAF</TITLE>
	<IMPLEMENTATION>
		<OS VALUE="Linux-ARMv7-A"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/startup.rtexe" TARGET="/home/lvuser/natinst/bin/startup.rtexe"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/startup.aliases" TARGET="/home/lvuser/natinst/bin/startup.aliases"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/data/ni_emb.dll" TARGET="/home/lvuser/natinst/bin/data/ni_emb.dll"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/amc-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/amc-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/CEF-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/CEF-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/CurrentValueTable-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/CurrentValueTable-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/DataDictionary-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/DataDictionary-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/TagBusModuleExecutionInterface-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/TagBusModuleExecutionInterface-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/TagBusModuleFramework-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/TagBusModuleFramework-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/TBDataFramework-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/TBDataFramework-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/ChineseS/LabVIEW Elemental IO-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/ChineseS/LabVIEW Elemental IO-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/English/LabVIEW Elemental IO-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/English/LabVIEW Elemental IO-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/English/LabVIEW FPGA IP Builder-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/English/LabVIEW FPGA IP Builder-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/English/LV-RepGenForMSOffice-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/English/LV-RepGenForMSOffice-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/French/LabVIEW Elemental IO-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/French/LabVIEW Elemental IO-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/French/LabVIEW FPGA IP Builder-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/French/LabVIEW FPGA IP Builder-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/German/LabVIEW Elemental IO-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/German/LabVIEW Elemental IO-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/German/LabVIEW FPGA IP Builder-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/German/LabVIEW FPGA IP Builder-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/Japanese/LabVIEW Elemental IO-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/Japanese/LabVIEW Elemental IO-errors.txt"/>
		<CODEBASE FILENAME="home/lvuser/natinst/bin/project/errors/Japanese/LabVIEW FPGA IP Builder-errors.txt" TARGET="/home/lvuser/natinst/bin/project/errors/Japanese/LabVIEW FPGA IP Builder-errors.txt"/>
		<DEPENDENCY TYPE="STRICT">
			<SOFTPKG NAME="{899452D2-C085-430B-B76D-7FDB33BB324A}" VERSION="14.0.1">
				<TITLE>LabVIEW Real-Time</TITLE>
			</SOFTPKG>
		</DEPENDENCY>
		<DEPENDENCY>
			<SOFTPKG NAME="{BE793622-69E8-4F0F-B3AB-DB06517FF276}" VERSION="16.0">
				<TITLE>CompactRIO Support</TITLE>
			</SOFTPKG>
		</DEPENDENCY>
		<DEPENDENCY>
			<SOFTPKG NAME="{4B855DFD-DF50-471B-B438-6096FD244423}" VERSION="4.3">
				<TITLE>NI Scan Engine</TITLE>
			</SOFTPKG>
		</DEPENDENCY>
		<DEPENDENCY>
			<SOFTPKG NAME="{56032245-0F4B-4641-9D74-33D067EB32B3}" VERSION="16.0">
				<TITLE>NI-RIO</TITLE>
			</SOFTPKG>
		</DEPENDENCY>
		<DEPENDENCY>
			<SOFTPKG NAME="{0EF06A82-BBC9-42BA-A68D-DEF017C23297}" VERSION="16.0">
				<TITLE>NI-RIO IO Scan</TITLE>
			</SOFTPKG>
		</DEPENDENCY>
		<MERGEINI TARGET="/ni-rt.ini">[LVRT]
RTTarget.ApplicationPath=/home/lvuser/natinst/bin/startup.rtexe
RTTarget.LaunchAppAtBoot=True

		</MERGEINI>
	</IMPLEMENTATION>
</SOFTPKG>
</DEFINITION>
