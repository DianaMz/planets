Resultados_hw3.pdf : Resultados_hw3.tex *.png *.jpg
	pdflatex Resultados_hw3.tex

*.png : Onda.py
	python Onda.py

*.jpg : Plots_Planetas.py *.txt
	python Plots_Planetas.py

*.txt : Planetas.x
	./Planetas.x

Planetas.x : Planetas.c
	cc Planetas.c -lm -o Planetas.x