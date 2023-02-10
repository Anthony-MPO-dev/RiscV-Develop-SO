muuu: interpreter.py test.cow
	@echo "\t" `python3 interpreter.py test.cow`

interpreter.py:
	@curl -O https://raw.githubusercontent.com/Mikhail57/cow-interpreter/master/interpreter.py

test.cow: 
	@curl -O https://raw.githubusercontent.com/Mikhail57/cow-interpreter/master/test.cow

clean: 
	@rm -f interpreter.py test.cow