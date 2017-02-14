INSERT INTO Professor (Codp,Nome,CPF,Salário)
VALUES (1,"Luciane Tramasso",12345678910,3550.00),
	(2,"Lucas Tramasso",41232922838,2500.00),
    (3,"Jose Elias da Silva",98765432110,5600.00),
    (4,"Marcella Alves de Souza", 10110110110,4500.00),
    (5,"Marianna Sona Leona", 01001001001,7500.00);
    
INSERT INTO Monitor(Codm,Nome,CPF,Salário)
VALUES	(1,"Pedro de Morais",10203040506,1350.00),
		(2,"Alice Tramasso",60504030201,1000.00);

INSERT INTO Curso(Codc,Codp,Nome,Data_Inicio,Data_Fim,Preço)
VALUES	(1,5,"Curso Básico de Confeitaria",'2015-10-16','2015-10-23',700.00),
		(2,1,"Massas e Molhos",'2015-10-16','2015-10-30',1100.00),
        (3,4,"Bolos e Tortas",'2015-10-23','2015-10-30',850.00);
        
INSERT INTO Monitoria(Codm,Codc)
VALUES	(1,1),
		(1,3),
        (2,2);

INSERT INTO Alunos(Matricula,Nome,CPF)
VALUES	(1,"Daniela",10000000001),
		(2,"Leonardo",11111111111),
        (3,"Renato",22222222222),
        (4,"Vinicius",33333333333),
        (5,"Gabriel",44444444444),
        (6,"Samuel",55555555555),
        (7,"Walter",66666666666),
        (8,"Marcelo",7777777777),
        (9,"Lavinnia",88888888888),
        (10,"Giovanna",99999999999);

INSERT INTO Aluno_Curso(Matricula,Codc)
VALUES	(1,1),(2,3),(3,1),(4,2),(5,1),(6,3),(7,2),(8,3),(9,2),(10,3);

INSERT INTO Receita(Codr,Nome)
VALUES	(1,"Bolo de Chocolate"),
		(2,"Lasanha a Bolonhesa"),
        (3,"Torta de Frutas Vermelhas"),
        (4,"Pesto alla genovese"),
        (5,"Bolo de Laranja"),
        (6,"Crème pâtissière");
        
INSERT INTO Receituario(Codr,Codc,Data)
VALUES	(1,1,'2015-10-16'),
		(1,3,'2015-10-25'),
        (2,2,'2015-10-16'),
        (3,3,'2015-10-26'),
        (4,2,'2015-10-17'),
        (5,1,'2015-10-17'),
        (5,3,'2015-10-27'),
        (6,1,'2015-10-18');
        
INSERT INTO Insumos(Codi,Nome,Tipo)
VALUES	(1,"Farinha","Alimento"),
		(2,"Chocolate em pó","Alimento"),
        (3,"Fermento em pó","Alimento"),
        (4,"Tomate","HortiFruti"),
        (5,"Morango","HortiFruti"),
        (6,"Framboesa","HortiFruti"),
        (7,"Manjericão","HortiFruti"),
        (8,"Azeite","Alimento"),
        (9,"Manteiga","Frios e Laticineos"),
        (10,"Laranja","HortiFrutti"),
        (11,"Baunilha(Fava)","HortiFrutti"),
        (12,"Carne Moída","Carnes"),
        (13,"Açúcar","Alimentos"),
        (14,"Ovos","HortiFrutti");

INSERT INTO Insumo_Receita(Codr,Codi,quantidade)
VALUES	(1,1,"200g"),(1,2,"50g"),(1,3,"5g"),(1,14,"3 unid"), /* Bolo de Chocolate */
		(2,1,"150g"),(2,3,"5g"),(2,4,"5 unid"),(2,12,"300g"), /* Lasanha */
        (3,1,"100g"),(3,5,"20 unid"),(3,6,"20 unid"),(3,9,"100g"),(3,11,"2 unid"),(3,13,"100g"),(3,14,"4 unid"), /* Torta */
		(4,8,"200ml"),(4,7,"100g"), /*pesto*/
        (5,1,"200g"),(5,3,"5g"),(5,10,"10 unid"),(5,13,"100g"),(5,14,"2 unid"), /* Bolo de Laranja */
        (6,9,"30g"),(6,11,"4 unid"),(6,13,"100g"),(6,14,"6 unid");
	

