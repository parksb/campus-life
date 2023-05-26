test:
	make test_default && make test_insert_3 && make test_insert_5 && make test_range && make test_delete_3 && make test_delete_5

test_default:
	python3 main.py < test_bp.txt > result.txt && diff result.txt gold.txt

test_insert_3:
	python3 main.py < test_insert_3.txt > result.txt && diff result.txt gold_insert_3.txt

test_insert_5:
	python3 main.py < test_insert_5.txt > result.txt && diff result.txt gold_insert_5.txt

test_range:
	python3 main.py < test_range.txt > result.txt && diff result.txt gold_range.txt

test_delete_3:
	python3 main.py < test_delete_3.txt > result.txt && diff result.txt gold_delete_3.txt

test_delete_5:
	python3 main.py < test_delete_5.txt > result.txt && diff result.txt gold_delete_5.txt
