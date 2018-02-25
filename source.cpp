#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WILLCLEAR true
#define WILLCLS false

typedef struct {
	char nome[20];
	int ra;
} aluno;

typedef struct {
	char nome[20];
	int id;
} disciplina;

typedef struct {
	char nome[20];
	int id;
} professor;

void printmenu();
void sanitizeInp(char*);
void clearscreen();

void printtabelaalunos(aluno*, int);
void printtabelaprofessores(professor*, int);
void printtabeladisciplinas(disciplina*, int);

enum menu { alunos = 1, disciplinas, professores, matriculas, desmatriculas, vincular, desvincular, printalu, printdis, printprof, printdisalu, printaludis, printdispro, printprodis, sair };

int main() {
	aluno		alunos[50];
	int qalunos = 0;
	disciplina	disciplinas[50];
	int qdisciplinas = 0;
	professor	professores[50];
	int qprofessores = 0;

	bool aludis[50][50] = { false };
	bool prodis[50][50] = { false };

	bool cont = true;
	bool count;
	menu op;
	int target;
	int it;
	int i;
	char l[2];
	int from[50];
	int willf;
	int to[50];
	int willt;
	int cf;
	int ct;

	while (cont) {
		printmenu();
		scanf("%i", &op);
		switch (op) {
		case menu::alunos:
			clearscreen();
			printf("\n\tQuantos alunos deseja cadastrar? ");
			scanf("%i", &it);
			printf("\t-----\n");
			for (i = 0; i < it; i++) {
				printf("\tDigite o nome do aluno %i: ", qalunos + 1);
				fgets(l, 2, stdin);
				fgets(alunos[qalunos].nome, 20, stdin);
				sanitizeInp(alunos[qalunos].nome);
				printf("\tDigite o RA do aluno %s: ", alunos[qalunos].nome);
				scanf("%i", &alunos[qalunos].ra);
				qalunos++;
				printf("\t-----\n");
			}
			break;
		case menu::disciplinas:
			clearscreen();
			printf("\n\tQuantas disciplinas deseja cadastrar? ");
			scanf("%i", &it);
			printf("\t-----\n");
			for (i = 0; i < it; i++) {
				printf("\tDigite o nome da disciplina %i: ", qdisciplinas + 1);
				fgets(l, 2, stdin);
				fgets(disciplinas[qdisciplinas].nome, 20, stdin);
				sanitizeInp(disciplinas[qdisciplinas].nome);
				printf("\tDigite o ID da disciplina %s: ", disciplinas[qdisciplinas].nome);
				scanf("%i", &disciplinas[qdisciplinas].id);
				qdisciplinas++;
				printf("\t-----\n");
			}
			break;
		case menu::professores:
			clearscreen();
			printf("\n\tQuantos professores deseja cadastrar? ");
			scanf("%i", &it);
			printf("\t-----\n");
			for (i = 0; i < it; i++) {
				printf("\tDigite o nome do professor %i: ", qprofessores + 1);
				fgets(l, 2, stdin);
				fgets(professores[qprofessores].nome, 20, stdin);
				sanitizeInp(professores[qprofessores].nome);
				printf("\tDigite o ID do professor %s: ", professores[qprofessores].nome);
				scanf("%i", &professores[qprofessores].id);
				qprofessores++;
				printf("\t-----\n");
			}
			break;
		case menu::matriculas:
			clearscreen();
			printf("\n\tQuantos alunos deseja matricular? ");
			scanf("%i", &willf);
			if (willf <= 0) break;
			printtabelaalunos(alunos, qalunos);
			for (i = 0; i < willf; i++) {
				printf("\tDigite o codigo referente ao aluno %i/%i: ", i + 1, willf);
				scanf("%i", &from[i]);
				from[i]--;
				printf("\tArmazenado aluno %s\n-----\n", alunos[from[i]].nome);
			}
			printf("\n\tEm quantas materias deseja matricular esses %i alunos? ", willf);
			scanf("%i", &willt);
			if (willt <= 0) break;
			printtabeladisciplinas(disciplinas, qdisciplinas);
			for (i = 0; i < willt; i++) {
				printf("\tDigite o codigo referente a disciplina %i/%i: ", i + 1, willt);
				scanf("%i", &to[i]);
				to[i]--;
				printf("\tArmazenada disciplina %s\n-----\n", disciplinas[to[i]].nome);
			}
			printf("\tMatriculando aluno(s)...\n");
			for (cf = 0; cf < willf; cf++) {
				for (ct = 0; ct < willt; ct++) {										
					//com grafos
					if (aludis[from[cf]][to[ct]]) {
						printf("\t\tAluno %s (RA %i) já estava matriculado em %s (ID %i)\n", alunos[from[cf]].nome, alunos[from[cf]].ra, disciplinas[to[ct]].nome, disciplinas[to[ct]].id);
					}
					else {
						printf("\t\tAluno %s (RA %i) matriculado em %s (ID %i)\n", alunos[from[cf]].nome, alunos[from[cf]].ra, disciplinas[to[ct]].nome, disciplinas[to[ct]].id);
					}
					aludis[from[cf]][to[ct]] = true;
				}
			}
			printf("\tMatricula(s) concluida(s)!\n");
			break;
		case menu::desmatriculas:
			clearscreen();
			printf("\n\tQuantos alunos deseja desmatricular? ");
			scanf("%i", &willf);
			if (willf <= 0) break;
			printtabelaalunos(alunos, qalunos);
			for (i = 0; i < willf; i++) {
				printf("\tDigite o codigo referente ao aluno %i/%i: ", i + 1, willf);
				scanf("%i", &from[i]);
				from[i]--;
				printf("\tArmazenado aluno %s\n-----\n", alunos[from[i]].nome);
			}
			printf("\n\tDe quantas materias deseja desmatricular esses %i alunos? ", willf);
			scanf("%i", &willt);
			if (willt <= 0) break;
			printtabeladisciplinas(disciplinas, qdisciplinas);
			for (i = 0; i < willt; i++) {
				printf("\tDigite o codigo referente a disciplina %i/%i: ", i + 1, willt);
				scanf("%i", &to[i]);
				to[i]--;
				printf("\tArmazenada disciplina %s\n-----\n", disciplinas[to[i]].nome);
			}
			printf("\tDesmatriculando alunos...\n");
			for (cf = 0; cf < willf; cf++) {
				for (ct = 0; ct < willt; ct++) {
					//com grafos
					if (aludis[from[cf]][to[ct]]) {
						printf("\t\tAluno %s (RA %i) desmatriculado de %s (ID %i)\n", alunos[from[cf]].nome, alunos[from[cf]].ra, disciplinas[to[ct]].nome, disciplinas[to[ct]].id);
					}
					else {
						printf("\t\tAluno %s (RA %i) não estava matriculado em %s (ID %i)\n", alunos[from[cf]].nome, alunos[from[cf]].ra, disciplinas[to[ct]].nome, disciplinas[to[ct]].id);
					}
					aludis[from[cf]][to[ct]] = false;
				}
			}
			printf("\tAluno(s) desmatriculado(s)!\n");
			break;
		case menu::vincular:
			clearscreen();
			printf("\n\tQuantos professores deseja vincular? ");
			scanf("%i", &willf);
			if (willf <= 0) break;
			printtabelaprofessores(professores, qprofessores);
			for (i = 0; i < willf; i++) {
				printf("\tDigite o codigo referente ao professor %i/%i: ", i + 1, willf);
				scanf("%i", &from[i]);
				from[i]--;
				printf("\tArmazenado professor %s\n-----\n", professores[from[i]].nome);
			}
			printf("\n\tEm quantas materias deseja vincular esses %i professores? ", willf);
			scanf("%i", &willt);
			if (willt <= 0) break;
			printtabeladisciplinas(disciplinas, qdisciplinas);
			for (i = 0; i < willt; i++) {
				printf("\tDigite o codigo referente a disciplina %i/%i: ", i + 1, willt);
				scanf("%i", &to[i]);
				to[i]--;
				printf("\tArmazenada disciplina %s\n-----\n", disciplinas[to[i]].nome);
			}
			printf("\tVinculando professores...\n");
			for (cf = 0; cf < willf; cf++) {
				for (ct = 0; ct < willt; ct++) {
					//com grafos
					if (prodis[from[cf]][to[ct]]) {
						printf("\t\tProfessor %s (ID %i) ja estava vinculado a %s (ID %i)\n", professores[from[cf]].nome, professores[from[cf]].id, disciplinas[to[ct]].nome, disciplinas[to[ct]].id);
					}
					else {
						printf("\t\tProfessor %s (ID %i) vinculado a %s (ID %i)\n", professores[from[cf]].nome, professores[from[cf]].id, disciplinas[to[ct]].nome, disciplinas[to[ct]].id);
					}
					prodis[from[cf]][to[ct]] = true;
				}
			}
			printf("\tVinculo concluido!\n");
			break;
		case menu::desvincular:
			clearscreen();
			printf("\n\tQuantos professores deseja desvincular? ");
			scanf("%i", &willf);
			if (willf <= 0) break;
			printtabelaprofessores(professores, qprofessores);
			for (i = 0; i < willf; i++) {
				printf("\tDigite o codigo referente ao professor %i/%i: ", i + 1, willf);
				scanf("%i", &from[i]);
				from[i]--;
				printf("\tArmazenado professor %s\n-----\n", professores[from[i]].nome);
			}
			printf("\n\tDe quantas materias deseja desvincular esses %i professores? ", willf);
			scanf("%i", &willt);
			if (willt <= 0) break;
			printtabeladisciplinas(disciplinas, qdisciplinas);
			for (i = 0; i < willt; i++) {
				printf("\tDigite o codigo referente a disciplina %i/%i: ", i + 1, willt);
				scanf("%i", &to[i]);
				to[i]--;
				printf("\tArmazenada disciplina %s\n-----\n", disciplinas[to[i]].nome);
			}
			printf("\tDesvinculando professores...\n");
			for (cf = 0; cf < willf; cf++) {
				for (ct = 0; ct < willt; ct++) {
					//com grafos
					if (prodis[from[cf]][to[ct]]) {
						printf("\t\tProfessor %s (ID %i) desvinculado de %s (ID %i)\n", professores[from[cf]].nome, professores[from[cf]].id, disciplinas[to[ct]].nome, disciplinas[to[ct]].id);
					}
					else {
						printf("\t\tProfessor %s (ID %i) não estava vinculado a %s (ID %i)\n", professores[from[cf]].nome, professores[from[cf]].id, disciplinas[to[ct]].nome, disciplinas[to[ct]].id);
					}
					prodis[from[cf]][to[ct]] = false;
				}
			}
			printf("\tProfessores desvinculados!\n");
			break;
		case menu::printalu:
			clearscreen();
			printf("\t-----\n");
			for (i = 0; i < qalunos; i++) {
				printf("\tAluno %i:\t %s \t- %i\n", i + 1, alunos[i].nome, alunos[i].ra);
			}
			printf("\n\t-----\n");
			break;
		case menu::printdis:
			clearscreen();
			printf("\t-----\n");
			for (i = 0; i < qdisciplinas; i++) {
				printf("\tDisciplina %i:\t %s \t- %i\n", i + 1, disciplinas[i].nome, disciplinas[i].id);
			}
			printf("\n\t-----\n");
			break;
		case menu::printprof:
			clearscreen();
			printf("\t-----\n");
			for (i = 0; i < qprofessores; i++) {
				printf("\tProfessor %i:\t %s \t- %i\n", i + 1, professores[i].nome, professores[i].id);
			}
			printf("\n\t-----\n");
			break;
		case menu::printaludis:
			clearscreen();
			printtabeladisciplinas(disciplinas, qdisciplinas);

			printf("\tDigite o codigo da disciplina que voce deseja verificar: ");
			scanf("%i", &target);
			target--;
			printf("\t-----\n");
			
			//com grafos
			printf("\tPara a disciplina %s constam os seguintes alunos:\n", disciplinas[target].nome);
			count = false;
			for (i = 0; i < 50; i++) {
				if (aludis[i][target]) {
					printf("\t\tAluno %s\t- %i\n", alunos[i].nome, alunos[i].ra);
					count = true;
				}
			}
			if (!count)
				printf("\tPara a disciplina %s nao constam alunos\n", disciplinas[target].nome);
			printf("\t-----\n");
			break;
		case menu::printdisalu:
			clearscreen();
			printtabelaalunos(alunos, qalunos);

			printf("\tDigite o codigo do aluno que voce deseja verificar: ");
			scanf("%i", &target);
			target--;
			printf("\t-----\n");

			//com grafos
			printf("\tPara o aluno %s constam as seguintes disciplinas:\n", alunos[target].nome);
			count = false;
			for (i = 0; i < 50; i++) {
				if (aludis[target][i]) {
					printf("\t\tDisciplina %s\t- %i\n", disciplinas[i].nome, disciplinas[i].id);
					count = true;
				}
			}
			if (!count)
				printf("\tPara o aluno %s nao constam disciplinas\n", alunos[target].nome);
																			
			printf("\t-----\n");
			break;
		case menu::printdispro:
			clearscreen();
			printtabelaprofessores(professores, qprofessores);

			printf("\tDigite o codigo do professor que voce deseja verificar: ");
			scanf("%i", &target);
			target--;
			printf("\t-----\n");

			//com grafos
			printf("\tPara o professor %s contam as seguintes disciplinas:\n", professores[target].nome);
			count = false;
			for (i = 0; i < 50; i++) {
				if (prodis[target][i]) {
					printf("\t\tDisciplina %s\t- %i\n", disciplinas[i].nome, disciplinas[i].id);
				}
			}
			if (!count)
				printf("\tPara o professor %s nao constam disciplinas\n", professores[target].nome);

			printf("\t-----\n");
			break;
		case menu::printprodis:
			clearscreen();
			printtabeladisciplinas(disciplinas, qdisciplinas);

			printf("\tDigite o codigo da disciplina que voce deseja verificar: ");
			scanf("%i", &target);
			target--;
			printf("\t-----\n");

			//com grafos
			printf("\tPara a disciplina %s contam os seguintes professores:\n", disciplinas[target].nome);
			count = false;
			for (i = 0; i < 50; i++) {
				if (prodis[i][target]) {
					printf("\t\tProfessor %s\t- %i\n", professores[i].nome, professores[i].id);
				}
			}
			if (!count)
				printf("\tPara a disciplina %s nao constam professores\n", disciplinas[target].nome);
			
			printf("\t-----\n");
			break;
		case menu::sair: cont = false; break;
		}
	}

	return 0;
}

void printtabelaalunos(aluno *t, int qd) {
	//printf("-----\n");
	printf("\n\tAlunos cadastrados:\n\n");
	int i;
	for (i = 0; i < qd; i++) {
		printf("\t\t%i\t\t-%s\n", i + 1, t[i].nome);
	}
	printf("\n\t-----\n\n");
}

void printtabeladisciplinas(disciplina *t, int qd) {
	//printf("-----\n");
	printf("\n\tDisciplinas cadastradas:\n\n");
	int i;
	for (i = 0; i < qd; i++) {
		printf("\t\t%i\t\t-%s\n", i + 1, t[i].nome);
	}
	printf("\n\t-----\n\n");
}

void printtabelaprofessores(professor *t, int qd) {
	//printf("-----\n");
	printf("\n\tProfessores cadastrados:\n\n");
	int i;
	for (i = 0; i < qd; i++) {
		printf("\t\t%i\t\t-%s\n", i + 1, t[i].nome);
	}
	printf("\n\t-----\n\n");
}

void sanitizeInp(char* inp) {
	char *p;
	p = strchr(inp, '\r');
	if (p != NULL) *p = '\0';
	p = strchr(inp, '\n');
	if (p != NULL) *p = '\0';
}

void clearscreen() {
	if (WILLCLEAR) system("clear");
	if (WILLCLS) system("cls");
}

void printmenu() {
	printf("\t----MENU---------------------------------------\n");
	printf("\t1_______________Cadastrar alunos_______________\n");
	printf("\t2____________Cadastrar disciplinas_____________\n");
	printf("\t3____________Cadastrar professores_____________\n");
	printf("\t4_______Matricular alunos em disciplinas_______\n");
	printf("\t5_____Desmatricular alunos em disciplinas______\n");
	printf("\t6______Vincular professores a disciplinas______\n");
	printf("\t7_Remover vinculo de professores e disciplinas_\n");
	printf("\t8________________Exibir alunos_________________\n");
	printf("\t9______________Exibir disciplinas______________\n");
	printf("\t10_____________Exibir professores______________\n");
	printf("\t11________Imprimir disciplinas de aluno________\n");
	printf("\t12________Imprimir alunos em disciplina________\n");
	printf("\t13______Imprimir disciplinas de professor______\n");
	printf("\t14_Imprimir professores vinculados a disciplina\n");
	printf("\t15____________________Sair_____________________\n");
	printf("\t-----------------------------------------------\n");
	printf("\n\tOpcao >> ");
}
