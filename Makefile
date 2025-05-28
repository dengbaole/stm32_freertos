project_name := stm32_rtos
uvproj_path := .
.PHONY: default build cformat format clean flash debug assets

build:
	@echo 【START】----- UV build -----
	@- UV4 -b $(uvproj_path)/$(project_name).uvprojx -j0 -o ./Output/Build_Output.txt
	@- powershell -c "cat $(uvproj_path)/Output/Build_Output.txt | sls 'Program Size'
	@- powershell -c "cat $(uvproj_path)/Output/Build_Output.txt | sls 'error'"
	@echo 【 END 】----- UV build -----

clean:
	@echo 【START】----- UV clean -----
	UV4 -c $(uvproj_path)/$(project_name).uvprojx -j0
	@echo 【 END 】----- UV clean -----

flash:
	@echo 【START】----- UV flash -----
	@- UV4 -b $(uvproj_path)/$(project_name).uvprojx -j0 -o ./Output/Build_Output.txt
	@- powershell -c "cat $(uvproj_path)/Output/Build_Output.txt | sls 'Program Size'
	@- powershell -c "cat $(uvproj_path)/Output/Build_Output.txt | sls 'error'"
	@- UV4 -f $(uvproj_path)/$(project_name).uvprojx -j0 -o ./Output/Program_Output.txt
	@- powershell -c cat $(uvproj_path)/Output/Program_Output.txt
	@echo 【 END 】----- UV flash -----


format:
	./utils_bin/astyle.exe --project="./utils_bin/.astylerc" -r **.c,**.h --ignore-exclude-errors --exclude=_build --exclude=utils_bin --exclude=dist --exclude=utils -v -Q



