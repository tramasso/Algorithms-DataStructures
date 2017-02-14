/* Quantidade de Receitas do Curso Bolos e Tortas */

SELECT count(Receita.Codr)
FROM Receita,Curso,Receituario
WHERE Receita.Codr = Receituario.Codr
AND Curso.Codc = Receituario.Codc
AND Curso.Nome = 'Bolos e Tortas';

/* Curso em que a aluna Daniela está Matriculada */

SELECT Curso.Nome
FROM Curso,Alunos,Aluno_Curso
WHERE Curso.Codc = Aluno_Curso.Codc
AND Alunos.Matricula = Aluno_Curso.Matricula
AND Alunos.Nome = 'Daniela';

/* Quantidade de Insumos diferentes utilizados no dia 16/10 */

SELECT count(Insumos.Codi)
FROM Insumos
WHERE Insumos.Codi IN
	(SELECT Insumo_Receita.Codi
		FROM Insumo_Receita
        WHERE Insumo_Receita.Codr IN
			(SELECT Receituario.Codr
				FROM Receituario
                WHERE Receituario.Data = '2015-10-16'));
			
/* Quem é o monitor da Lavinnia? */

SELECT Monitor.Nome
FROM Monitor
WHERE Monitor.Codm IN
	(SELECT Monitoria.Codm
		FROM Monitoria
        WHERE Monitoria.Codc IN
			(SELECT Aluno_Curso.Codc
				FROM Aluno_Curso
				WHERE Aluno_Curso.Matricula IN
					(SELECT Alunos.Matricula
						FROM Alunos
                        WHERE Alunos.Nome = 'Lavinnia')));
                        
/* Para quantos alunos a prof Luciane dá Aula?? */

SELECT COUNT(Alunos.Matricula)
FROM Alunos,Aluno_Curso,Curso,Professor
WHERE Aluno_Curso.Matricula = Alunos.Matricula	
AND Aluno_Curso.Codc = Curso.Codc
AND Curso.Codp = Professor.Codp
AND Professor.Nome = 'Luciane Tramasso';				
					
                    
/* Quantidade de Alunos em cada Curso */

SELECT Curso.Nome, COUNT(Alunos.Matricula)
FROM Alunos,Curso,Aluno_Curso	
WHERE Alunos.Matricula = Aluno_Curso.Matricula
AND Curso.Codc = Aluno_Curso.Codc
GROUP BY Curso.Nome;

/* Cursos que recebem mais do que 2500 reais e a quantidade de alunos neles */

SELECT Curso.Nome, count(Alunos.Matricula)
FROM Curso,Alunos,Aluno_Curso
WHERE Curso.Codc = Aluno_Curso.Codc
AND Alunos.Matricula = Aluno_Curso.Matricula
GROUP BY Curso.Nome
HAVING SUM(Curso.Preço) >= 2500;

/* Receitas que são feitas em mais de um Curso  */

SELECT Receita.Nome
FROM Receita,Receituario,Curso
WHERE Receita.Codr = Receituario.Codr
AND Curso.Codc = Receituario.Codc
GROUP BY Receita.Nome
HAVING COUNT(Curso.Codc) > 1;

/* Receitas Realizadas entre os dias 16-10-2015 e 23-10-2015 que utilizam mais do que 3 insumos */

SELECT Receita.Nome
FROM Receita,Insumos,Insumo_Receita,Receituario
WHERE Receita.Codr = Insumo_Receita.Codr
AND Insumo_Receita.Codi = Insumos.Codi
AND Receita.Codr = Receituario.Codr
AND Receituario.Data BETWEEN '2015-10-16'AND '2015-10-23'
GROUP BY Receita.Nome
HAVING COUNT(Insumos.Codi) > 3;


/* Lista de todos os professores, e o curso que ministra se caso ministrar algum curso */

SELECT Professor.Nome,Curso.Nome
FROM Professor
	LEFT JOIN Curso ON Professor.Codp = Curso.Codp;
    
/* Lista de Professores,nome das Receitas a serem feitas e dia em que deve ser feita se caso existir alguma receita */

SELECT Professor.Nome,Receituario.Data,Receita.Nome
FROM Professor
	LEFT JOIN Curso ON Curso.Codp = Professor.Codp
    LEFT JOIN Receituario ON Receituario.Codc = Curso.Codc
    LEFT JOIN Receita ON Receita.Codr = Receituario.Codr
	ORDER BY Receituario.Data
