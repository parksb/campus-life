test:
	make test_default && make test_insert_3 && make test_insert_5 && make test_range && make test_delete_3 && make test_delete_3m && make test_delete_5 && make test_delete_5m && make test_ad_hoc

test_default:
	python3 main.py < test_bp.txt > result.txt && delta result.txt gold.txt

test_insert_3:
	python3 main.py < test_insert_3.txt > result.txt && delta result.txt gold_insert_3.txt

test_insert_5:
	python3 main.py < test_insert_5.txt > result.txt && delta result.txt gold_insert_5.txt

test_range:
	python3 main.py < test_range.txt > result.txt && delta result.txt gold_range.txt

test_delete_3:
	python3 main.py < test_delete_3.txt > result.txt && delta result.txt gold_delete_3.txt

test_delete_3m:
	python3 main.py < test_delete_3m.txt > result.txt && delta result.txt gold_delete_3m.txt

test_delete_5:
	python3 main.py < test_delete_5.txt > result.txt && delta result.txt gold_delete_5.txt

test_delete_5m:
	python3 main.py < test_delete_5m.txt > result.txt && delta result.txt gold_delete_5m.txt

test_ad_hoc:
	python3 main.py < test_ad_hoc.txt > result.txt && delta result.txt gold_ad_hoc.txt
