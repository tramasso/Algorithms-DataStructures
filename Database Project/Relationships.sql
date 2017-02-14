CREATE TABLE Professor(
	Codp int,
    Nome varchar(30) not null,
    CPF varchar(14) not null,
    Salário float,
    PRIMARY KEY (Codp)
);

CREATE TABLE Monitor(
	Codm int,
    Nome varchar(30) not null,
    CPF varchar(14) not null,
    Salário float,
    PRIMARY KEY (Codm)
);



CREATE TABLE Curso(
		Codc int,
		Codp int,
        Nome varchar(30) not null,
        Data_Inicio date,
        Data_Fim date,
        Preço float,
        PRIMARY KEY (Codc,Codp),
        FOREIGN KEY (Codp) REFERENCES Professor(Codp)
);	
CREATE TABLE Monitoria(
	Codm int,
    Codc int,
    PRIMARY KEY(Codm,Codc),
    FOREIGN KEY (Codm) REFERENCES Monitor(Codm),
    FOREIGN KEY (Codc) REFERENCES Curso(Codc)
);

CREATE TABLE Alunos(
	Matricula int,
    Nome varchar(30),
    CPF varchar(14) not null,
    PRIMARY KEY (Matricula)
);
CREATE TABLE Aluno_Curso(
	Matricula int,	
    Codc int,
    PRIMARY KEY (Matricula,Codc),
    FOREIGN KEY (Matricula) REFERENCES Alunos(Matricula),
    FOREIGN KEY (Codc) REFERENCES Curso(Codc) 
);

CREATE TABLE Receita(
	Codr int,
    Nome varchar(30),
	PRIMARY KEY (Codr)
);
CREATE TABLE Receituario(
	Codr int,
    Codc int,
    Data date,
    PRIMARY KEY (Codr,Codc),
    FOREIGN KEY (Codr) REFERENCES Receita(Codr),
    FOREIGN KEY (Codc) REFERENCES Curso(Codc)
);
CREATE TABLE Insumos(
	Codi int,
    Nome varchar(30),
    Tipo varchar(30),
	PRIMARY KEY (Codi)
);    

CREATE TABLE Insumo_Receita(
	Codr int,
    Codi int,
    quantidade varchar(30),
	PRIMARY KEY (Codr,Codi),
    FOREIGN KEY (Codr) REFERENCES Receita(Codr),
    FOREIGN KEY (Codi) REFERENCES Insumos(Codi)
);







