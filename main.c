#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <locale.h>
#include <time.h>

#define TAM_MAXLINHA 200
#define MAX_ANIMAIS 100
#define MAX_DONOS 100
#define MAX_INTERVENCOES 100
#define MAX_VETERINARIOS 2
#define HORARIO_ABERTURA 830 // 8:30h
#define HORARIO_FECHAMENTO 1800 // 18:00h

void capitalize(char *str) { //recebe uma string passa a primeira letra a Maiúscula e o restante a minúsculas 
    int len = strlen(str);
    int capitalizeNext = 1;

    for (int i = 0; i < len; ++i) {
        if (isspace(str[i])) {
            capitalizeNext = 1;
        } else if (capitalizeNext) {
            str[i] = toupper(str[i]);
            capitalizeNext = 0;
        } else {
            str[i] = tolower(str[i]);
        }
    }
}

void minutosParaHoras(int minutos, int *horas, int *minutosRestantes) {//converte um valor de minutos em horas e minutos restantes
    *horas = minutos / 60;
    *minutosRestantes = minutos % 60;
}

int VERIFICARDATA(char *Data) // recebe uma string com "dia-mês-ano" e verifica se essa data é posterior à data atual
{ 
	time_t tempoAtual;
	struct tm *infoTempo;
	time(&tempoAtual);
	infoTempo = localtime(&tempoAtual);

	int diaAtual = infoTempo->tm_mday;
	int mesAtual = infoTempo->tm_mon + 1;
	int anoAtual = infoTempo->tm_year + 1900;

	int dia, mes, ano;
	sscanf(Data, "%d-%d-%d", &dia, &mes, &ano);

	if (ano < anoAtual || (ano == anoAtual && mes < mesAtual) || (ano == anoAtual && mes == mesAtual && dia < diaAtual))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int DEVOLVEPOS(ANIMAL listaAnimais[], int num_animais, int id_animal) //vai buscar um animal na lista pelo seu ID e retorna a posição do animal na lista. Se o animal não for encontrado,retorna -1.
{
	if (listaAnimais != NULL && id_animal > 0)
	{
		for (int i = 0; i < num_animais; i++)
		{
			if (listaAnimais[i].ID == id_animal)
			{
				return i;
				break;
			}
		}
	}
	return -1;
}

int DEVOLVEPOSDONO(DONO listaDonos[], int num_donos, int id_dono)////vai buscar um dono na lista pelo seu ID e retorna a posição do dono na lista. Se o dono não for encontrado,retorna -1.
{
	if (listaDonos != NULL && id_dono > 0)
	{
		for (int i = 0; i < num_donos; i++)
		{
			if (listaDonos[i].ID == id_dono)
			{
				return i;
				break;
			}
		}
	}
	return -1;
}

int DEVOLVEULTIMOID_ANIMAL(ANIMAL listaAnimais[], int num_animais)//vai buscar o último ID de animal na lista de animais e retorna esse valor
{
	int ultimoid = 0;

	if (listaAnimais != NULL && num_animais > 0)
	{
		for (int i = 0; i < num_animais; i++)
		{
			ultimoid = listaAnimais[i].ID;
		}
	}
	return ultimoid;
}

int VERIFICANIF_DONO(DONO listaDonos[], int num_donos, int NIF)
{
    int usado = 0;
    if (listaDonos != NULL && num_donos > 0)
    {
        for (int i = 0; i < num_donos; i++)
        {
            if (listaDonos[i].NIF == NIF)
            {
                usado = 1;
                break; // Como já encontramos o NIF, podemos sair do loop
            }
        }
    }
    return usado;
}


void ADICIONARANIMAL(ANIMAL listaAnimais[], int *num_animais, DONO listaDonos[], int *num_donos)
{
	ANIMAL novo_animal;
	DONO novo_dono;
	int numWords = 0;
	int count=0;
	FILE *ficheiro_animais = fopen("animais.txt", "a");
	FILE *ficheiro_donos = fopen("donos.txt", "a");

	int existe = 0;

	if (ficheiro_animais == NULL && ficheiro_donos == NULL)
	{
		printf("Erro ao abrir os ficheiros.");
		return;
	}
	printf("______________________________________________________________________");
	printf("\n\t\tPreenchimento do Animal\n");
	printf("______________________________________________________________________\n");
	// Le e guarda os dados
	novo_animal.ID = DEVOLVEULTIMOID_ANIMAL(listaAnimais, *num_animais) + 1;
do {
        // Reinicia o contador de palavras

        printf("Nome do animal: ");
        fgets(novo_animal.NOME, sizeof(novo_animal.NOME), stdin);
        novo_animal.NOME[strcspn(novo_animal.NOME, "\n")] = '\0'; // Remove a nova linha

        // Verifica se o nome está preenchido e se tem até 20 caracteres
        if (strlen(novo_animal.NOME) == 0 || strlen(novo_animal.NOME) > 20) {
            printf("AVISO!!!!O nome deve ter até 20 caracteres. .\n");
        } else {
            // Verifica se o nome tem até dois nomes
            for (int i = 0; i < strlen(novo_animal.NOME); i++) {
                if (isspace(novo_animal.NOME[i])) {
                    numWords++;
                }
            }
            if (numWords > 1) {
                printf("O nome não pode ter mais de 1 nome. Tente novamente.\n");
            } else {
                // Convertendo para o formato desejado
                capitalize(novo_animal.NOME);
            }
        }
    } while (strlen(novo_animal.NOME) == 0 || strlen(novo_animal.NOME) > 20 || numWords > 1);


	do {
        printf("Especie: ");
        fgets(novo_animal.ESPECIE, sizeof(novo_animal.ESPECIE), stdin);
        novo_animal.ESPECIE[strcspn(novo_animal.ESPECIE, "\n")] = '\0'; // Remove a nova linha

        // Verifica se a ESPECIE está preenchido e se tem até 20 caracteres
        if (strlen(novo_animal.ESPECIE) == 0 || strlen(novo_animal.ESPECIE) > 20) {
            printf("O nome deve ter ate 20 caracteres. Tente novamente.\n");
        } else {
            // Verifica se o nome tem até dois nomes

            for (int i = 0; i < strlen(novo_animal.ESPECIE); i++) {
                if (isspace(novo_animal.ESPECIE[i])) {
                    numWords++;
                }
            }
            if (numWords > 1) {
                printf("A Especie não pode ter mais de dois nomes. Tente novamente.\n");
            } else {
                // Convertendo para o formato desejado
                capitalize(novo_animal.ESPECIE);
            }
        }
    } while (strlen(novo_animal.ESPECIE) == 0 || strlen(novo_animal.ESPECIE) > 20 || numWords > 1);

	/*printf("Raça do animal: ");
	scanf("%s", novo_animal.RACA);*/
	do {
        printf("Raca do animal: ");
        fgets(novo_animal.RACA, sizeof(novo_animal.RACA), stdin);
        novo_animal.RACA[strcspn(novo_animal.RACA, "\n")] = '\0'; // Remove a nova linha

        // Verifica se a ESPECIE está preenchido e se tem até 20 caracteres
        if (strlen(novo_animal.RACA) == 0 || strlen(novo_animal.RACA) > 20) {
            printf("O nome deve ter ate 20 caracteres. Tente novamente.\n");
        } else {
            // Verifica se o nome tem até dois nomes

            for (int i = 0; i < strlen(novo_animal.RACA); i++) {
                if (isspace(novo_animal.RACA[i])) {
                    numWords++;
                }
            }
            if (numWords > 1) {
                printf("A raça não pode ter mais de dois nomes. Tente novamente.\n");
            } else {
                // Convertendo para o formato desejado
                capitalize(novo_animal.RACA);
            }
        }
    } while (strlen(novo_animal.RACA) == 0 || strlen(novo_animal.RACA) > 20 || numWords > 1);
	do {
        printf("Gênero do animal (M/F): ");
        scanf(" %c",&novo_animal.GENERO);
        novo_animal.GENERO = toupper(novo_animal.GENERO ); // Convertendo para maiúscula
        if (novo_animal.GENERO  != 'M' && novo_animal.GENERO  != 'F') {
            printf("Por favor, insira apenas 'M' ou 'F'.\n");
        }
    } while (novo_animal.GENERO  != 'M' && novo_animal.GENERO  != 'F');
	printf("Peso do animal (use ','): ");
    scanf("%f", &novo_animal.PESO);
	printf("\nO dono do animal já está registado no programa? (0 - Não | 1 - Sim): ");
	scanf("%d", &existe);


	if (existe == 1)
	{
		// printf("%d", num_animais);
		MOSTRARDADOSDONOS(listaDonos, *num_donos);
		printf("ID do dono do animal: ");
		scanf("%d", &novo_animal.ID_DONO);
	}
	else
	{

		novo_dono.ID = DEVOLVEULTIMOID_DONO(listaDonos, *num_donos) + 1;
			do {
			    printf("NIF do dono (deve ter 9 digitos): ");
			    scanf("%d", &novo_dono.NIF);
			    getchar(); // Limpa o buffer de entrada
			
			    if (novo_dono.NIF < 100000000 || novo_dono.NIF > 999999999) {
			        printf("O NIF deve ter 9 digitos. Tente novamente.\n");
			    } else if (VERIFICANIF_DONO(listaDonos, *num_donos, novo_dono.NIF)) {
			        printf("Este NIF já está em uso. Por favor, escolha outro.\n");
			    }
			} while (novo_dono.NIF < 100000000 || novo_dono.NIF > 999999999 || VERIFICANIF_DONO(listaDonos, *num_donos, novo_dono.NIF));



			do {
			    printf("Nome do dono(Primeiro ou Apelido): ");
			    fgets(novo_dono.NOME, sizeof(novo_dono.NOME), stdin);
			    novo_dono.NOME[strcspn(novo_dono.NOME, "\n")] = '\0'; // Remove a nova linha

			    // Verifica se o nome está preenchido e se tem até 50 caracteres
			    if (strlen(novo_dono.NOME) == 0 || strlen(novo_dono.NOME) > 50) {
			        printf("O nome deve ter um nome ou o apelido. Tente novamente.\n");
			    } else {
			        int numWords = 1; // Inicializado para 1 para contar a primeira palavra
			        // Verifica se o nome tem até dois nomes

			        for (int i = 0; i < strlen(novo_dono.NOME); i++) {
			            if (isspace(novo_dono.NOME[i])) {
			                numWords++;
			            }
			        }
			        if (numWords > 2) {
			            printf("O nome não pode ter mais de dois nomes. Tente novamente.\n");
			        } else {
			            // Convertendo para o formato desejado
			            capitalize(novo_dono.NOME);
			        }
			    }
			} while (strlen(novo_dono.NOME) == 0 || strlen(novo_dono.NOME) > 50 || numWords > 2);


			do {
			    printf("Cidade do dono: ");
			    fgets(novo_dono.CIDADE, sizeof(novo_dono.CIDADE), stdin);
			    novo_dono.CIDADE[strcspn(novo_dono.CIDADE, "\n")] = '\0'; // Remove a nova linha

			    // Verifica se a CIDADE está preenchida
			    if (strlen(novo_dono.CIDADE) == 0) {
			        printf("A CIDADE não pode estar vazia. Tente novamente.\n");
			    }
			    else {
			        // Convertendo para o formato desejado
			        capitalize(novo_dono.CIDADE);
			    }
			} while (strlen(novo_dono.CIDADE) == 0);

			do {
			    printf("Contacto do dono (deve começar com 2, 91, 93 ou 96 e ter 9 digitos): ");
			    scanf("%d", &novo_dono.TELEFONE);
			    getchar(); // Limpa o buffer de entrada

			    // Verifica se o telefone começa com 2, 91, 93 ou 96
			    if (!(novo_dono.TELEFONE >= 200000000 && novo_dono.TELEFONE <= 299999999) &&
			        !(novo_dono.TELEFONE >= 910000000 && novo_dono.TELEFONE <= 919999999) &&
			        !(novo_dono.TELEFONE >= 930000000 && novo_dono.TELEFONE <= 939999999) &&
			        !(novo_dono.TELEFONE >= 960000000 && novo_dono.TELEFONE <= 969999999)) {
			        printf("O número de telefone deve começar com 2, 91, 93 ou 96. Tente novamente.\n");
			        continue;
			    }

			    // Verifica se o telefone tem exatamente 9 dígitos
			    int num = novo_dono.TELEFONE;

			    while (num != 0) {
			        num /= 10;
			        count++;
			    }
			    if (count != 9) {
			        printf("O número de telefone deve ter 9 digitos. Tente novamente.\n");
			    }
			} while (count != 9);

		novo_animal.ID_DONO = novo_dono.ID;

		// printf("%d", *num_donos);
		// Adiciona o dono ao vetor donos
		listaDonos[*num_donos] = novo_dono;
		// Incrementa o contador dos donos
		(*num_donos)++;
	}
	// Adiciona o animal ao vetor animais
	listaAnimais[*num_animais] = novo_animal;
	// Adicona mais um ao contador de animais
	(*num_animais)++;

	if (fprintf(ficheiro_animais, "\n%d\t %s\t %s\t %s\t %c\t %.2f\t %d",
				novo_animal.ID,
				novo_animal.NOME,
				novo_animal.ESPECIE,
				novo_animal.RACA,
				novo_animal.GENERO,
				novo_animal.PESO,
				novo_animal.ID_DONO) &&
		fprintf(ficheiro_donos, "\n%d\t%d\t%s\t%s\t%d",
				novo_dono.ID,
				novo_dono.NIF,
				novo_dono.NOME,
				novo_dono.CIDADE,
				novo_dono.TELEFONE))
	{
		printf("Animal adicionado com sucesso!");
	}
	else
	{
		printf("Erro ao adicionar o animal");
	}
	fclose(ficheiro_animais);
	fclose(ficheiro_donos);
}

void CARREGARDADOSINTERVENCOES(INTERVENCAO listaIntervencoes[], int *num_intervencoes)// le a info de intervenções do arquivi txt, converte para o formato apropriado e as guarda em uma lista de intervenções, atualizando o contador de intervenções à medida que avança
{
	FILE *ficheiro;
	ficheiro = fopen("intervencoes.txt", "r");

	if (ficheiro == NULL)
	{
		printf("Erro ao abrir o ficheiro.\n");
		return;
	}

	char linha[TAM_MAXLINHA];

	while (fgets(linha, TAM_MAXLINHA, ficheiro) != NULL)
	{
		sscanf(linha, "%d\t%d\t%d\t%d\t%s\t%s\t%f",
			   &listaIntervencoes[*num_intervencoes].ID,
			   &listaIntervencoes[*num_intervencoes].TIPO_INTERVENCAO,
			   &listaIntervencoes[*num_intervencoes].ID_VETERINARIO,
			   &listaIntervencoes[*num_intervencoes].ID_ANIMAL,
			   &listaIntervencoes[*num_intervencoes].DATA,
			   &listaIntervencoes[*num_intervencoes].HORA,
			   &listaIntervencoes[*num_intervencoes].CUSTO);

		(*num_intervencoes)++;
	}

	fclose(ficheiro);
}


int validarHora(const char *hora) { 
    int horaInt, minutoInt;
    if (sscanf(hora, "%d:%d", &horaInt, &minutoInt) != 2) {
        return 0; // Falha na leitura dos valores de hora e minuto
    }
    if (horaInt < 0 || horaInt > 23) {
        return 0; // Hora fora do intervalo válido
    }
    if (minutoInt < 0 || minutoInt > 59) {
        return 0; // Minuto fora do intervalo válido
    }
    return 1; // Hora válida
}


void AGENDARINTERVENCAO(VETERINARIO listaVeterinarios[], int num_veterinarios, INTERVENCAO listaIntervencoes[], int *num_intervencoes, ANIMAL listaAnimais[], int num_animais) {
    FILE *ficheiro;
    ficheiro = fopen("intervencoes.txt", "a");
    INTERVENCAO nova_intervencao;

    int teste = OBTERIDULTIMAINTERVENCAO(listaIntervencoes, *num_intervencoes) + 1;

    nova_intervencao.ID = teste;
    int tipo_intervencao = 0, id_vet, id_ani;

    do {
        printf("Tipo de intervenção\n1-Consulta\t2-Vacinacao\t3-Cirurgia\n");
        scanf("%d", &tipo_intervencao);

        if (tipo_intervencao < 1 || tipo_intervencao > 3) {
            printf("\nErro! Tipo de intervenção inválida.\n");
        }
    } while (tipo_intervencao < 1 || tipo_intervencao > 3);

    nova_intervencao.TIPO_INTERVENCAO = tipo_intervencao;
    MOSTRAVETERINARIOS(listaVeterinarios, num_veterinarios);
    printf("\nDigite o id do veterinario: ");
    scanf("%d", &id_vet);

    if (VERIFICAR_ID_VETERINARIO(listaVeterinarios, num_veterinarios, id_vet) == 1) {
        nova_intervencao.ID_VETERINARIO = id_vet;

        // Verifica se o veterinário tem tempo disponível suficiente para uma cirurgia
        if (nova_intervencao.TIPO_INTERVENCAO == 3) { // Verifica se é cirurgia
            // Verifica se o veterinário tem pelo menos 2 horas disponíveis
            if (listaVeterinarios[id_vet].HORAS_TRABALHADAS + 120 > HORARIO_FECHAMENTO - HORARIO_ABERTURA) {
                printf("\nErro! Veterinário não tem tempo suficiente disponível para realizar uma cirurgia.\n");
                return;
            }
        } else { // Para consultas e vacinações (blocos de meia hora)
            // Verifica se o veterinário tem pelo menos meia hora disponível
            if (listaVeterinarios[id_vet].HORAS_TRABALHADAS + 30 > (HORARIO_FECHAMENTO - HORARIO_ABERTURA)) {
                printf("\nErro! Veterinário não tem tempo suficiente disponível para realizar uma consulta ou vacinação.\n");
                return;
            }
        }
    } else {
        printf("\nErro! ID de veterinario invalido.\n");
        return;
    }

    MOSTRARDADOSANIMAIS(listaAnimais, num_animais);
    printf("\nDigite o id do animal: ");
    scanf("%d", &id_ani);

    if (VERIFICAR_ID_ANIMAL(listaAnimais, num_animais, id_ani) == 1) {
        nova_intervencao.ID_ANIMAL = id_ani;
    } else {
        printf("\nErro! ID de animal invalido.\n");
        return;
    }

    printf("\nData (ex: 01-01-2023): ");
    scanf("%s", nova_intervencao.DATA);

    char hora[6];
    do {
        printf("\nHora (ex: 14:30): ");
        scanf("%s", hora);
        if (!validarHora(hora)) {
            printf("\nErro! Hora inválida.\n");
        }
    } while (!validarHora(hora));

    strcpy(nova_intervencao.HORA, hora);

    printf("\nPreco (EX: 10,5): ");
    scanf("%f", &nova_intervencao.CUSTO);

    // Verifica se já existe uma intervenção agendada para a mesma data e hora
    for (int i = 0; i < *num_intervencoes; i++) {
        if (strcmp(nova_intervencao.DATA, listaIntervencoes[i].DATA) == 0 &&
            strcmp(nova_intervencao.HORA, listaIntervencoes[i].HORA) == 0) {
            printf("\nErro! Já existe uma intervencao agendada para esta data e hora.\n");
            return;
        }
    }

    // Adiciona a nova intervenção à lista de intervenções
    listaIntervencoes[*num_intervencoes] = nova_intervencao;
    (*num_intervencoes)++;

    if (ficheiro == NULL) {
        printf("Erro ao abrir ficheiro!\n");
        return;
    }

    // Escrevendo os dados no arquivo
    fprintf(ficheiro, "%d\t%d\t%d\t%d\t%s\t%s\t%.2f\n",
        nova_intervencao.ID,
        nova_intervencao.TIPO_INTERVENCAO,
        nova_intervencao.ID_VETERINARIO,
        nova_intervencao.ID_ANIMAL,
        nova_intervencao.DATA,
        nova_intervencao.HORA,
        nova_intervencao.CUSTO);

    fclose(ficheiro);

    printf("Intervencao marcada com sucesso!\n");
}



int VERIFICAR_ID_VETERINARIO(VETERINARIO listaVeterinarios[], int num_veterinarios, int id)
{
	int existe = 0;
	if (listaVeterinarios != NULL && num_veterinarios > 0)
	{
		for (int i = 0; i < num_veterinarios; i++)
		{
			if (listaVeterinarios[i].ID == id)
				;
			existe = 1;
		}
	}
	return existe;
}

int VERIFICAR_ID_ANIMAL(ANIMAL listaAnimal[], int num_animais, int id)
{
	int existe = 0, contador;
	if (listaAnimal != NULL && num_animais > 0)
	{
		for (int i = 0; i < num_animais; i++)
		{
			// printf("\n ID ANIMAL %d = %d ID VERIFICAR\n", listaAnimal[i].ID, id);
			if (listaAnimal[i].ID == id)
			{
				existe = 1;
			}
		}
	}
	return existe;
}

int VERIFICAR_ID_DONO(DONO listaDono[], int num_donos, int id)
{
	int existe = 0;
	if (listaDono != NULL && num_donos > 0)
	{
		for (int i = 0; i < num_donos; i++)
		{
			if (listaDono[i].ID == id)
				;
			existe = 1;
		}
	}
	return existe;
}

void MOSTRAINTERVENCOES(INTERVENCAO listaIntervencoes[], int num_intervencoes)
{
	if (listaIntervencoes == NULL)
	{
		printf("Erro ao listar veterinários\n");
	}
	else
	{
		printf("\n\t\tINTERVENCOES\n");
		printf("ID\tTIPO_INTVENCAO\tID_VET\tID_ANIMAL\tDATA\tHORA\tCUSTO\n");
		printf("-------------------------------------------------------------\n");
		for (int i = 0; i < num_intervencoes; i++)
		{
			printf("%d\t%d\t%d\t%d\t%s\t%s\t%.2f\n",
       					listaIntervencoes[i].ID,
       					listaIntervencoes[i].TIPO_INTERVENCAO,
       					listaIntervencoes[i].ID_VETERINARIO,
       					listaIntervencoes[i].ID_ANIMAL,
       					listaIntervencoes[i].DATA,
      					listaIntervencoes[i].HORA,
      			 		listaIntervencoes[i].CUSTO);
		}
		printf("\n-------------------------------------------------------------\n");
	}
}

int OBTERIDULTIMAINTERVENCAO(INTERVENCAO listaIntervencoes[], int num_intervencoes)
{
	int ultimo_id = 0;
	if (listaIntervencoes != NULL && num_intervencoes > 0)
	{
		for (int i = 0; i < num_intervencoes; i++)
		{
			ultimo_id = listaIntervencoes[i].ID;
		}
	}
	return ultimo_id;
}

void ADICIONARVETERINARIO(VETERINARIO listaVeterinarios[], int *num_veterinarios)
{
	int quantia = *num_veterinarios;
	int numWords=0;
	int count=0;
	if (quantia < 2)
	{
		VETERINARIO novo_veterinario;
		int NIF, CONTACTO, aux = 0;

		novo_veterinario.ID = DEVOLVEULTIMOID_ANIMAL(listaVeterinarios, quantia) + 1;
		do {
	        printf("NIF do Veterinario (deve ter 9 digitos): ");
	        scanf("%d", &NIF);
	        getchar(); // Limpa o buffer de entrada

	        if (NIF < 100000000 || NIF > 999999999) {
	            printf("O NIF deve ter 9 digitos. Tente novamente.\n");
	        }
    	} while (NIF < 100000000 || NIF > 999999999);
		aux = VERIFICANIF(listaVeterinarios, quantia, NIF);
		if (aux == 1)
		{
			printf("Erro! NIF em utilização.");
			return;
		}
		else
		{
			novo_veterinario.NIF = NIF;
		}

		do {
	        printf("Nome do Veterinario(Primeiro ou Apelido) : ");
	        fgets(novo_veterinario.NOME, sizeof(novo_veterinario.NOME), stdin);
	        novo_veterinario.NOME[strcspn(novo_veterinario.NOME, "\n")] = '\0'; // Remove a nova linha

	        if (strlen(novo_veterinario.NOME) == 0 || strlen(novo_veterinario.NOME) > 20) {
	            printf("O nome deve ter até 20 caracteres. Tente novamente.\n");
	        } else {
	            // Verifica se o nome tem até dois nomes
	            int numWords = 0;
	            for (int i = 0; i < strlen(novo_veterinario.NOME); i++) {
	                if (isspace(novo_veterinario.NOME[i])) {
	                    numWords++;
	                }
	            }
	            if (numWords > 1) {
	                printf("O nome não pode ter mais de dois nomes. Tente novamente.\n");
	            } else {
	                // Convertendo para o formato desejado
	                capitalize(novo_veterinario.NOME);
	            }
	        }
	    } while (strlen(novo_veterinario.NOME) == 0 || strlen(novo_veterinario.NOME) > 20 || numWords > 1);

		do {
	        printf("Nome do Especialidade : ");
	        fgets(novo_veterinario.ESPECIALIDADE, sizeof(novo_veterinario.ESPECIALIDADE), stdin);
	        novo_veterinario.ESPECIALIDADE[strcspn(novo_veterinario.ESPECIALIDADE, "\n")] = '\0'; // Remove a nova linha

	        // Verifica se a especialidade está preenchido e se tem até 50 caracteres
	        if (strlen(novo_veterinario.ESPECIALIDADE) == 0 || strlen(novo_veterinario.ESPECIALIDADE) > 50) {
	            printf("O especialidade deve ter até 20 caracteres. Tente novamente.\n");
	        } else {
	            // Verifica se o nome tem até dois nomes
	            int numWords = 0;
	            for (int i = 0; i < strlen(novo_veterinario.ESPECIALIDADE); i++) {
	                if (isspace(novo_veterinario.ESPECIALIDADE[i])) {
	                    numWords++;
	                }
	            }
	            if (numWords > 1) {
	                printf("O especialidade não pode ter mais de dois nomes. Tente novamente.\n");
	            } else {
	                // Convertendo para o formato desejado
	                capitalize(novo_veterinario.ESPECIALIDADE);
	            }
	        }
	    } while (strlen(novo_veterinario.ESPECIALIDADE) == 0 || strlen(novo_veterinario.ESPECIALIDADE) > 20 || numWords > 1);

		do {
	        printf("TELEDFONE do veterinario(deve começar com 2, 91, 93 ou 96 e ter 9 digitos): ");
	        scanf("%d", &novo_veterinario.TELEFONE);
	        getchar(); // Limpa o buffer de entrada

	        // Verifica se o telefone começa com 2, 91, 93 ou 96
	        if (!(novo_veterinario.TELEFONE >= 200000000 && novo_veterinario.TELEFONE <= 299999999) &&
	            !(novo_veterinario.TELEFONE >= 910000000 && novo_veterinario.TELEFONE <= 919999999) &&
	            !(novo_veterinario.TELEFONE >= 930000000 && novo_veterinario.TELEFONE <= 939999999) &&
	            !(novo_veterinario.TELEFONE >= 960000000 && novo_veterinario.TELEFONE <= 969999999)) {
	            printf("O número de telefone deve começar com 2, 91, 93 ou 96. Tente novamente.\n");
	            continue;
	        }

	        // Verifica se o telefone tem exatamente 9 dígitos
	        int num = novo_veterinario.TELEFONE;

	        while (num != 0) {
	            num /= 10;
	            count++;
	        }
	        if (count != 9) {
	            printf("O número de telefone deve ter 9 digitos. Tente novamente.\n");
	        }
	    } while (count != 9);

		novo_veterinario.HORAS_TRABALHADAS = 0;

		listaVeterinarios[*num_veterinarios] = novo_veterinario;
		(*num_veterinarios)++;

		FILE *ficheiro = fopen("veterinarios.txt", "a");
		if (ficheiro == NULL)
		{
			printf("Erro ao abrir o ficheiro.");
			return;
		}

		if (fprintf(ficheiro, "\n%d\t %d\t %s\t %s\t %d\t %d",
					novo_veterinario.ID,
					novo_veterinario.NIF,
					novo_veterinario.NOME,
					novo_veterinario.ESPECIALIDADE,
					novo_veterinario.TELEFONE,
					novo_veterinario.HORAS_TRABALHADAS))
		{
			printf("Veterinario adicionado com sucesso!");
		}
		else
		{
			printf("Erro ao adicionar o veterinário!");
			return;
		}
		fclose(ficheiro);
	}
	else
	{
		printf("Erro! Nao e possivel adicionar mais veterinarios (Limite de %d alcançado!)", MAX_VETERINARIOS);
		return;
	}
}

int VERIFICANIF(VETERINARIO listaVeterinarios[], int num_veterinarios, int NIF)
{
	int usado = 0;
	if (listaVeterinarios != NULL && num_veterinarios > 0)
	{
		for (int i = 0; i < num_veterinarios; i++)
		{
			if (listaVeterinarios[i].NIF == NIF)
			{
				usado = 1;
			}
		}
	}
	return usado;
}

void CARREGARDADOSVETERINARIOS(VETERINARIO *veterinarios, int *num_veterinarios) {
    FILE *ficheiro;
    ficheiro = fopen("veterinarios.txt", "r");

    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    char linha[TAM_MAXLINHA];

    while (fgets(linha, TAM_MAXLINHA, ficheiro) != NULL) {
        sscanf(linha, "%d %d %s %s %d %f",
            &veterinarios[*num_veterinarios].ID,
            &veterinarios[*num_veterinarios].NIF,
            &veterinarios[*num_veterinarios].NOME,
            &veterinarios[*num_veterinarios].ESPECIALIDADE,
            &veterinarios[*num_veterinarios].TELEFONE,
            &veterinarios[*num_veterinarios].HORAS_TRABALHADAS);

        (*num_veterinarios)++;
    }

    fclose(ficheiro);
}


void MOSTRAVETERINARIOS(VETERINARIO veterinarios[], int num_veterinarios) {
    if (veterinarios == NULL) {
        printf("\nErro ao listar veterinarios\n");
    } else {
        printf("\tVETERINARIOS\n");
        printf("ID\tNIF\tNOME\tESPECIALIDADE\tTELEFONE\tHORAS_TRAB\n");
        printf("-------------------------------------------------------------\n");
        for (int i = 0; i < num_veterinarios; i++) {
            // Calcula as horas e minutos totais
            int horas = veterinarios[i].HORAS_TRABALHADAS / 60;
            int minutos = veterinarios[i].HORAS_TRABALHADAS % 60;

            printf("\nVeterinario ID %d\n", veterinarios[i].ID);
            printf("%d\t%d\t%s\t%s\t%d\t%d horas e %d minutos",
                veterinarios[i].ID,
                veterinarios[i].NIF,
                veterinarios[i].NOME,
                veterinarios[i].ESPECIALIDADE,
                veterinarios[i].TELEFONE,
                horas,
                minutos);
        }
        printf("\n-------------------------------------------------------------\n");
    }
}


void CARREGARDADOSDONOS(DONO *donos, int *num_donos)
{
	FILE *ficheiro;
	ficheiro = fopen("donos.txt", "r");

	if (ficheiro == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	char linha[TAM_MAXLINHA];

	while (fgets(linha, TAM_MAXLINHA, ficheiro) != NULL)
	{
		sscanf(linha, "%d %d %s %s %d",
			   &donos[*num_donos].ID,
			   &donos[*num_donos].NIF,
			   &donos[*num_donos].NOME,
			   &donos[*num_donos].CIDADE,
			   &donos[*num_donos].TELEFONE);

		(*num_donos)++;
	}

	fclose(ficheiro);
}

void LISTAANIMAISDONOS(ANIMAL listaAnimais[], DONO listaDonos[], int num_animais, int num_donos)
{

	printf("\nANIMAIS E RESPETIVOS DONOS\n");
	printf("-------------------------------------------------------------");
	for (int i = 0; i < num_donos; i++)
	{
		printf("\n#ID Dono %d", listaDonos[i].ID);

		int quantiaAnimais = QUANTIAANIMAIS(listaAnimais, num_animais, listaDonos[i].ID);

		if (quantiaAnimais > 0)
		{
			for (int x = 0; x < num_animais; x++)
			{

				if (listaAnimais[x].ID_DONO == listaDonos[i].ID)
				{

					printf("\n%d\t %s\t %s\t %s\t %c\t %.2f\t %d",
						   listaAnimais[x].ID,
						   listaAnimais[x].NOME,
						   listaAnimais[x].ESPECIE,
						   listaAnimais[x].RACA,
						   listaAnimais[x].GENERO,
						   listaAnimais[x].PESO,
						   listaAnimais[x].ID_DONO);
				}
			}
		}
		else
		{
			printf("\nNao tem qualquer animal registado.");
		}
		
	}
	printf("\n-------------------------------------------------------------\n");
}

int DEVOLVEULTIMOID_VETERINARIO(VETERINARIO listaVeterinarios[], int num_veterinarios)
{
	int ultimoid = 0;

	if (listaVeterinarios != NULL && num_veterinarios > 0)
	{
		for (int i = 0; i < num_veterinarios; i++)
		{
			ultimoid = listaVeterinarios[i].ID;
		}
	}
	return ultimoid;
}

int DEVOLVEULTIMOID_DONO(DONO listaDonos[], int num_donos)
{
	int ultimoid = 0;

	if (listaDonos != NULL && num_donos > 0)
	{
		for (int i = 0; i < num_donos; i++)
		{
			ultimoid = listaDonos[i].ID;
		}
	}
	return ultimoid;
}

int QUANTIAANIMAIS(ANIMAL listaAnimais[], int num_animais, int id)
{
	int quantia = 0;
	for (int i = 0; i < num_animais; i++)
	{
		if (listaAnimais[i].ID_DONO == id)
		{
			quantia++;
		}
	}
	return quantia;
}

void CARREGARDADOSANIMAIS(ANIMAL *animais, int *num_animais)
{
	FILE *ficheiro;
	ficheiro = fopen("animais.txt", "r");

	if (ficheiro == NULL)
	{
		printf("Erro ao abrir o arquivo.animais\n");
		return;
	}

	char linha[TAM_MAXLINHA];
	while (fgets(linha, TAM_MAXLINHA, ficheiro) != NULL)
	{
		sscanf(linha, "%d %s %s %s %c %f %d",
			   &animais[*num_animais].ID,
			   &animais[*num_animais].NOME,
			   &animais[*num_animais].ESPECIE,
			   &animais[*num_animais].RACA,
			   &animais[*num_animais].GENERO,
			   &animais[*num_animais].PESO,
			   &animais[*num_animais].ID_DONO);

		(*num_animais)++;
	}

	fclose(ficheiro);
}

void MOSTRARDADOSANIMAIS(ANIMAL animais[], int num_animais)
{
	printf("\n\t\tANIMAIS\n");
	printf("ID\t NOME\t ESPECIE\t RACA\t GENERO\t PESO\t ID_DONO\n");
	printf("-------------------------------------------------------------\n");
	for (int i = 0; i < num_animais; i++)
	{
		printf("%d\t %s\t %s\t %s\t %c\t %.2f\t %d\n",
			   animais[i].ID,
			   animais[i].NOME,
			   animais[i].ESPECIE,
			   animais[i].RACA,
			   animais[i].GENERO,
			   animais[i].PESO,
			   animais[i].ID_DONO);
	}
	printf("-------------------------------------------------------------\n");
}

void MOSTRARDADOSDONOS(DONO donos[], int num_donos)
{
	printf("\n\t\tDONOS\n");
	printf("ID\tNIF\t NOME\t CIDADE\t TELEFONE\n");
	printf("-------------------------------------------------------------\n");
	for (int i = 0; i < num_donos; i++)
	{
		printf("%d\t%d\t %s\t %s\t %d\n",
			   donos[i].ID,
			   donos[i].NIF,
			   donos[i].NOME,
			   donos[i].CIDADE,
			   donos[i].TELEFONE);
	}
	printf("-------------------------------------------------------------\n");
}

int *DEVOLVEIDSANIMAISDONO(ANIMAL listaAnimais[], int num_animais, int id_dono)
{
	// printf("teste %d", *num_animais);
	// printf("%d", num_animais);
	int *animaisDoDono = (int *)malloc(num_animais * sizeof(int)); // Vetor para armazenar IDs
	int contador = 0;

	if (listaAnimais != NULL && num_animais > 0)
	{
		for (int i = 0; i < num_animais; i++)
		{
			if (listaAnimais[i].ID_DONO == id_dono)
			{
				animaisDoDono[contador++] = listaAnimais[i].ID;
				printf("%d\n", listaAnimais[i].ID);
			}
		}
	}
	return animaisDoDono;
}

void DETERMINARCUSTOTOTALINTERVENCOES_IDANIMAL(INTERVENCAO listaIntervencoes[], int num_intervencoes) {
    int id_animal;
    printf("Digite o id do animal: ");
    scanf("%d", &id_animal);

    float valor_total = 0.0; // Initialize as 0.0 to ensure correct starting value

    if (listaIntervencoes != NULL) {
        for (int i = 0; i < num_intervencoes; i++) {
            if (listaIntervencoes[i].ID_ANIMAL == id_animal) {
                if (VERIFICARDATA(listaIntervencoes[i].DATA) == 1) {
                    valor_total += (float)listaIntervencoes[i].CUSTO; // Convert to float if necessary
                }
            }
        }
    }

    // Check if the animal ID was found in the list of interventions
    if (valor_total > 0.0) {
        printf("[Animal ID %d] - Valor total gasto: %.2f euros\n", id_animal, valor_total);
    } else {
        printf("[Animal ID %d] - Não foram encontradas intervenções para este animal.\nERRO NA PROCURA!", id_animal);
    }
}


void DETERMINARCUSTOTOTALINTERVENCOES_IDDONO(INTERVENCAO listaIntervencoes[], int num_intervencoes, int id_dono, const char data_limite[]) {
    float valor_total = 0.0; // Inicializa como 0.0 para garantir o valor inicial correto

    if (listaIntervencoes != NULL) {
        for (int i = 0; i <num_intervencoes; i++) {
            // Verifica se o ID do dono coincide e se a data da intervenção é posterior à data limite
            if (listaIntervencoes[i].ID_ANIMAL == id_dono && strcmp(listaIntervencoes[i].DATA, data_limite) > 0) {
                valor_total += listaIntervencoes[i].CUSTO; // Acumula o custo
            }
        }
    }

    // Verifica se foram encontradas intervenções para o dono após a data limite
    if (valor_total > 0.0) {
        printf("[Dono ID %d] - Valor total gasto após %s: %.2f euros\n", id_dono, data_limite, valor_total);
    } else {
        printf("[Dono ID %d] - Não foram encontradas intervenções para este dono após %s.\nERRO NA PROCURA!", id_dono, data_limite);
    }
}




int COMPARAR(const void *a, const void *b)
{
	float diferenca = (*(float *)b - *(float *)a);
	if (diferenca > 0)
		return 1;
	else if (diferenca < 0)
		return -1;
	else
		return 0;
}

void LISTA_INTERVENCOESDATA(INTERVENCAO listaIntervencoes[], int *num_intervencoes, char *data)
{
	printf("\nIntervencoes: (%s)\n", data);
	int encontrados = 0;

	for (int i = 0; i < num_intervencoes; i++)
	{
		if (strcmp(listaIntervencoes[i].DATA, data) == 0)
		{
			encontrados++;
			printf("%d\t%d\t%d\t%d\t%s\t%s\t%.2f\n",
       					listaIntervencoes[i].ID,
       					listaIntervencoes[i].TIPO_INTERVENCAO,
       					listaIntervencoes[i].ID_VETERINARIO,
       					listaIntervencoes[i].ID_ANIMAL,
       					listaIntervencoes[i].DATA,
      					listaIntervencoes[i].HORA,
      			 		listaIntervencoes[i].CUSTO);
		}
	}
	printf("\nForam encontrados %d registos.\n", encontrados);
}

int dataEstaNoIntervalo(const char *data_verificar, const char *data_inicio, const char *data_fim) {
    struct tm tm_verificar, tm_inicio, tm_fim;

    memset(&tm_verificar, 0, sizeof(struct tm));
    memset(&tm_inicio, 0, sizeof(struct tm));
    memset(&tm_fim, 0, sizeof(struct tm));

    sscanf(data_verificar, "%d-%d-%d", &tm_verificar.tm_mday, &tm_verificar.tm_mon, &tm_verificar.tm_year);
    sscanf(data_inicio, "%d-%d-%d", &tm_inicio.tm_mday, &tm_inicio.tm_mon, &tm_inicio.tm_year);
    sscanf(data_fim, "%d-%d-%d", &tm_fim.tm_mday, &tm_fim.tm_mon, &tm_fim.tm_year);

    tm_verificar.tm_year -= 1900; // Corrigir o ano
    tm_verificar.tm_mon -= 1;     // Corrigir o mês
    tm_inicio.tm_year -= 1900;
    tm_inicio.tm_mon -= 1;
    tm_fim.tm_year -= 1900;
    tm_fim.tm_mon -= 1;

    time_t timestamp_verificar = mktime(&tm_verificar);
    time_t timestamp_inicio = mktime(&tm_inicio);
    time_t timestamp_fim = mktime(&tm_fim);

    return (timestamp_verificar >= timestamp_inicio && timestamp_verificar < timestamp_fim);
}

void LISTA_INTERVENCOESVETERINARIO_DATA(INTERVENCAO listaIntervencoes[], int num_intervencoes) {
    char data_inicio[11];
    char data_fim[11];
    int id_veterinario;

    printf("\nDigite o id do veterinario: ");
    scanf("%d", &id_veterinario);
    printf("\nDigite a data inicial (xx-xx-xxxx): ");
    scanf("%10s", data_inicio);
    printf("\nDigite a data final (xx-xx-xxxx): ");
    scanf("%10s", data_fim);

    for (int i = 0; i < num_intervencoes; i++) {
        int esta_no_intervalo = dataEstaNoIntervalo(listaIntervencoes[i].DATA, data_inicio, data_fim);

        if (esta_no_intervalo) {
            printf("%s esta no intervalo.\n", listaIntervencoes[i].DATA);
        } else {
            printf("%s nao esta no intervalo.\n", listaIntervencoes[i].DATA);
        }
    }
}


int DEVOLVEPOSVET(VETERINARIO listaVeterinarios[], int num_veterinarios, int id_veterinario)
{
	if (listaVeterinarios != NULL && id_veterinario > 0)
	{
		for (int i = 0; i < num_veterinarios; i++)
		{
			if (listaVeterinarios[i].ID == id_veterinario)
			{
				return i;
				break;
			}
		}
	}
	return -1;
}

void ELIMINARDONO(DONO listaDonos[], int *num_donos, ANIMAL listaAnimais[], int *num_animais)
{
	int id_dono, contagem = 0;


	printf("%d - %d", num_donos, *num_donos);

	MOSTRARDADOSDONOS(listaDonos, *num_donos);

	printf("\nDigite o ID do dono que deseja remover: ");
	scanf("%d", &id_dono);

	if (id_dono > 0)
	{
		if (VERIFICAR_ID_DONO(listaDonos, *num_donos, id_dono) == 1)
		{
			int posicao = DEVOLVEPOSDONO(listaDonos, *num_donos, id_dono);

			if (posicao != -1)
			{

				MOSTRARDADOSANIMAIS(listaAnimais, num_animais);

				for (int i = 0; i < num_animais; i++)
				{
					if (listaAnimais[i].ID_DONO == id_dono)
					{
						listaAnimais[i].ID_DONO = 0;
						contagem++;
					}
				}

				MOSTRARDADOSANIMAIS(listaAnimais, num_animais);

				if (contagem > 0)
				{
					// Faz a alteração no ficheiro animais.txt
					FILE *ficheiro_animais;
					ficheiro_animais = fopen("animais.txt", "w");

					if (ficheiro_animais != NULL)
					{
						for (int y = 0; y < num_animais; y++)
						{
							fprintf(ficheiro_animais, "%d\t%s\t%s\t%s\t%c\t%.2f\t%d\n",
									listaAnimais[y].ID,
									listaAnimais[y].NOME,
									listaAnimais[y].ESPECIE,
									listaAnimais[y].RACA,
									listaAnimais[y].GENERO,
									listaAnimais[y].PESO,
									listaAnimais[y].ID_DONO);
						}

						fclose(ficheiro_animais);
					}
					else
					{
						printf("\nErro ao abrir ficheiro!\n");
						return;
					}
				}
				

				printf("%d - %d", posicao, *num_donos);

				for (int i = posicao; i < *num_donos - 1; i++)
				{
					listaDonos[i] = listaDonos[i + 1];
				}
				(*num_donos)--;


				FILE *ficheiro_donos;
				ficheiro_donos = fopen("donos.txt", "w");


				if (ficheiro_donos != NULL)
				{
					for (size_t x = 0; x < *num_donos; x++)
					{
						fprintf(ficheiro_donos, "%d\t%d\t%s\t%s\t%d\n",
								listaDonos[x].ID,
								listaDonos[x].NIF,
								listaDonos[x].NOME,
								listaDonos[x].CIDADE,
								listaDonos[x].TELEFONE);
					}

					fclose(ficheiro_donos);
					printf("\nDono removido com sucesso!\n");
				}
			}
			else
			{
				printf("\nERRO - Posição não encontrada!\n");
			}
		}
		else
		{
			printf("\nNão foi possível encontrar este ID\n");
		}
	}
	else
	{
		printf("\nERRO - ID inválido\n");
	}
}

void ELIMINARANIMAL(ANIMAL listaAnimais[], int *num_animais)
{
	int id_animal;
	printf("\nId do animal: ");
	scanf("%d", &id_animal);
	if (listaAnimais != NULL && id_animal > 0)
	{
		int posicao = DEVOLVEPOS(listaAnimais, *num_animais, id_animal);

		if (posicao != -1)
		{
			for (int i = posicao; i < *num_animais - 1; i++)
			{
				listaAnimais[i] = listaAnimais[i + 1];
			}
			(*num_animais)--;

			FILE *ficheiro;
			ficheiro = fopen("animais.txt", "w");

			if (ficheiro != NULL)
			{
				for (int y = 0; y < *num_animais; y++)
				{
					fprintf(ficheiro, "\n%d\t %s\t %s\t %s\t %c\t %.2f\t %d",
							listaAnimais[y].ID,
							listaAnimais[y].NOME,
							listaAnimais[y].ESPECIE,
							listaAnimais[y].RACA,
							listaAnimais[y].GENERO,
							listaAnimais[y].PESO,
							listaAnimais[y].ID_DONO);
				}

				fclose(ficheiro);
				printf("\nAnimal removido com sucesso!\n");
			}
			else
			{
				printf("\nErro ao abrir ficheiro!\n");
				return;
			}
		}
		else
		{
			printf("Posição do animal não encontrado!");
		}
	}
}

void ELIMINARVETERINARIO(VETERINARIO listaVeterinarios[], int *num_veterinarios, INTERVENCAO listaIntervencoes[], int *num_intervencoes)
{
	int id_veterinario, contagem;

	MOSTRAVETERINARIOS(listaVeterinarios, *num_veterinarios);

	printf("\nDigite o id: ");
	scanf("%d", &id_veterinario);

	if (listaVeterinarios != NULL && id_veterinario > 0)
	{
		int posicao = DEVOLVEPOSVET(listaVeterinarios, *num_veterinarios, id_veterinario);
		if (posicao != 1)
		{
			MOSTRAINTERVENCOES(listaIntervencoes, *num_intervencoes);
			for (int i = 0; i < *num_intervencoes; i++)
			{
				if (listaIntervencoes[i].ID_VETERINARIO == id_veterinario)
				{
					listaIntervencoes[i].ID_VETERINARIO = 0;
					contagem++;
				}
			}
			MOSTRAINTERVENCOES(listaIntervencoes, *num_intervencoes);

			if (contagem > 0)
			{
				// Faz a alteração no ficheiro intervencoes.txt
				FILE *ficheiro_intervencoes;
				ficheiro_intervencoes = fopen("intervencoes.txt", "w");

				if (ficheiro_intervencoes != NULL)
				{
					for (int y = 0; y < *num_intervencoes; y++)
					{
						fprintf(ficheiro_intervencoes, "%d\t%d\t%d\t%d\t%s\t%.2f\n",
								listaIntervencoes[y].ID,
								listaIntervencoes[y].TIPO_INTERVENCAO,
								listaIntervencoes[y].ID_VETERINARIO,
								listaIntervencoes[y].ID_ANIMAL,
								listaIntervencoes[y].DATA,
								listaIntervencoes[y].CUSTO);
					}

					fclose(ficheiro_intervencoes);
				}
				else
				{
					printf("\nErro ao abrir ficheiro!\n");
					return;
				}
			}

			for (int i = posicao; i < *num_veterinarios - 1; i++)
			{
				listaVeterinarios[i] = listaVeterinarios[i + 1];
			}
			(*num_veterinarios)--;

			FILE *ficheiro_vet;
			ficheiro_vet = fopen("veterinarios.txt", "w");

			if (ficheiro_vet != NULL)
			{
				for (int j = 0; j < *num_veterinarios; j++)
				{
					fprintf(ficheiro_vet, "%d\t%d\t%s\t%s\t%d\t%d\n",
							listaVeterinarios[j].ID,
							listaVeterinarios[j].NIF,
							listaVeterinarios[j].NOME,
							listaVeterinarios[j].ESPECIALIDADE,
							listaVeterinarios[j].TELEFONE,
							listaVeterinarios[j].HORAS_TRABALHADAS);
				}
				fclose(ficheiro_vet);
				printf("\nVeterinario removido com sucesso!\n");
			}
			else
			{
				printf("\nErro ao abrir ficheiro!\n");
				return;
			}
		}
		else
		{
			printf("Posição do veterinario não encontrado!");
		}
	}
	else
	{
		printf("\nERRO - Não foi possivel encontrar este id!\n");
		return;
	}
}

void limparBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}



void EDITARDONO(DONO listaDonos[], int num_donos)
{
	system("cls");
	MOSTRARDADOSDONOS(listaDonos, num_donos);
	int id;
	int numWords=0;
	int count=0;
	printf("\nID do dono: ");
	scanf("%d", &id);

	// Verificar se o id existe já há uma função para isso. É para trocar.
	if (VERIFICAR_ID_DONO(listaDonos, &num_donos, id) == 1)
	{
		DONO dono_editado;
		for (int i = 0; i < num_donos; i++)
		{
			if (listaDonos[i].ID == id)
			{
				dono_editado.ID = listaDonos[i].ID;
				printf("\nNIF : %d ", listaDonos[i].NIF);
				printf("\nNome : %s", listaDonos[i].NOME);
				printf("\nCidade antiga: %s ", listaDonos[i].CIDADE);
				do {
				    printf("Nova Cidade: ");
				    fgets(listaDonos[i].CIDADE, sizeof(listaDonos[i].CIDADE), stdin);
				    listaDonos[i].CIDADE[strcspn(listaDonos[i].CIDADE, "\n")] = '\0'; // Remove a nova linha

				    // Verifica se a CIDADE está preenchida e se tem até 20 caracteres
				    if (strlen(listaDonos[i].CIDADE) == 0 || strlen(listaDonos[i].CIDADE) > 20) {
				        printf("A cidade deve ter até 20 caracteres. Tente novamente.\n");
				    } else {
				        // Verifica se a cidade tem até dois nomes
				        int numWords = 1; // O primeiro "nome" é garantido

				        for (int j = 0; j < strlen(listaDonos[i].CIDADE); j++) {
				            if (isspace(listaDonos[i].CIDADE[j])) {
				                numWords++;
				            }
				        }
				        if (numWords > 1) {
				            printf("A cidade não pode ter mais de um nome. Tente novamente.\n");
				        } else {
				            // Convertendo para o formato desejado
				            capitalize(listaDonos[i].CIDADE);
				        }
				    }
				} while (strlen(listaDonos[i].CIDADE) == 0 || strlen(listaDonos[i].CIDADE) > 20 || numWords > 1);

				printf("\nTELEFONE antigo: %d ", listaDonos[i].TELEFONE);
				do {
				    printf("\tNovo telefone (deve começar com 2, 91, 93 ou 96 e ter 9 dígitos): ");
				    scanf("%d", &listaDonos[i].TELEFONE);
				    getchar(); // Limpa o buffer de entrada

				    // Verifica se o telefone começa com 2, 91, 93 ou 96
				    if (!(listaDonos[i].TELEFONE >= 200000000 && listaDonos[i].TELEFONE <= 299999999) &&
				        !(listaDonos[i].TELEFONE >= 910000000 && listaDonos[i].TELEFONE <= 919999999) &&
				        !(listaDonos[i].TELEFONE >= 930000000 && listaDonos[i].TELEFONE <= 939999999) &&
				        !(listaDonos[i].TELEFONE >= 960000000 && listaDonos[i].TELEFONE <= 969999999)) {
				        printf("O número de telefone deve começar com 2, 91, 93 ou 96. Tente novamente.\n");
				        continue;
				    }

				    // Verifica se o telefone tem exatamente 9 dígitos
				    int num = listaDonos[i].TELEFONE;
				    int count = 0;

				    while (num != 0) {
				        num /= 10;
				        count++;
				    }
				    if (count != 9) {
				        printf("O número de telefone deve ter 9 dígitos. Tente novamente.\n");
				    }
				} while (count != 9);

			}
		}

		FILE *ficheiro = fopen("donos.txt", "w");
		if (ficheiro == NULL)
		{
			printf("Erro ao abrir o ficheiro para escrita.\n");
			return;
		}
		else
		{
			for (int i = 0; i < num_donos; i++)
			{
				fprintf(ficheiro, "%d\t%d\t%s\t%s\t%d\n",
						listaDonos[i].ID,
						listaDonos[i].NIF,
						listaDonos[i].NOME,
						listaDonos[i].CIDADE,
						listaDonos[i].TELEFONE);
			}
		}

		fclose(ficheiro);

		printf("Dono editado com sucesso!\n");
	}
	else
	{
		printf("\nERRO - Dono não encontrado!\n");
		return;
	}
}

void EDITARANIMAL(ANIMAL listaAnimais[], int num_animais, DONO listaDonos[],int num_donos)
{
	system("cls");
	MOSTRARDADOSANIMAIS(listaAnimais, num_animais);
	int id;

	printf("\nID do animal: ");
	scanf("%d", &id);

	printf("%d %d", num_animais, &num_animais);
	printf("\nPAROU AQUI\n");

	// Verificar se o id existe já há uma função para isso. É para trocar.
	if (VERIFICAR_ID_ANIMAL(listaAnimais, num_animais, id) == 1)
	{
		printf("\nPAROU AQUI\n");
		ANIMAL animal_editado;
		for (int i = 0; i < num_animais; i++)
		{
			if (listaAnimais[i].ID == id)
			{
				animal_editado.ID = listaAnimais[i].ID;
				printf("\nNome: %s", listaAnimais[i].NOME);
				printf("\nEspecie : %s", listaAnimais[i].ESPECIE);
				printf("\nRaca : %s ", listaAnimais[i].RACA);
				printf("\nGenero : %c", listaAnimais[i].GENERO);
				printf("\n(Peso antigo: %.2f) Novo peso(use ','): ", listaAnimais[i].PESO);
				scanf("%f", &listaAnimais[i].PESO);

				printf("\n---------------------------------------------------------------\n");
				printf("\nO dono registados no programa\n");

				MOSTRARDADOSDONOS(listaDonos, num_donos);

				printf("\n(ID_Dono antigo: %d) Novo ID do Dono: ", listaAnimais[i].ID_DONO);
				scanf("%d", &listaAnimais[i].ID_DONO);
			}
		}

		FILE *ficheiro = fopen("animais.txt", "w");
		if (ficheiro == NULL)
		{
			printf("Erro ao abrir o ficheiro para escrita.\n");
			return;
		}
		else
		{
			for (int i = 0; i < num_animais; i++)
			{
				fprintf(ficheiro, "%d\t%s\t%s\t%s\t%c\t%.2f\t%d\n",
						listaAnimais[i].ID,
						listaAnimais[i].NOME,
						listaAnimais[i].ESPECIE,
						listaAnimais[i].RACA,
						listaAnimais[i].GENERO,
						listaAnimais[i].PESO,
						listaAnimais[i].ID_DONO);
			}
		}

		fclose(ficheiro);

		printf("Animal editado com sucesso!\n");
	}
	else
	{
		printf("\nERRO - Animal não encontrado!\n");
		return;
	}
}
void EDITARVETERINARIO(VETERINARIO listaVeterinarios[], int num_veterinarios) {
    system("cls");
    MOSTRAVETERINARIOS(listaVeterinarios, num_veterinarios);
    int id;
    int count = 0;
    printf("\nID do veterinario: ");
    scanf("%d", &id);
    getchar(); // Limpa o buffer de entrada

    int encontrado = 0; // Flag para indicar se o veterinário foi encontrado

    for (int i = 0; i < num_veterinarios; i++) {
        if (listaVeterinarios[i].ID == id) {
            encontrado = 1; // Veterinário encontrado

            printf("\nNIF : %d", listaVeterinarios[i].NIF);
            printf("\nNome : %s ", listaVeterinarios[i].NOME);
            printf("\n(Especialidade antiga: %s) Nova Especialidade: ", listaVeterinarios[i].ESPECIALIDADE);
            scanf("%s", listaVeterinarios[i].ESPECIALIDADE);
            capitalize(listaVeterinarios[i].ESPECIALIDADE);
            getchar(); // Limpa o buffer de entrada

            printf("\n(TELEFONE antigo: %d)", listaVeterinarios[i].TELEFONE);
            do {
                printf("\tNovo telefone (deve começar com 2, 91, 93 ou 96 e ter 9 dígitos): ");
                scanf("%d", &listaVeterinarios[i].TELEFONE);
                getchar(); // Limpa o buffer de entrada

                // Verifica se o telefone começa com 2, 91, 93 ou 96
                if (!(listaVeterinarios[i].TELEFONE >= 200000000 && listaVeterinarios[i].TELEFONE <= 299999999) &&
                    !(listaVeterinarios[i].TELEFONE >= 910000000 && listaVeterinarios[i].TELEFONE <= 919999999) &&
                    !(listaVeterinarios[i].TELEFONE >= 930000000 && listaVeterinarios[i].TELEFONE <= 939999999) &&
                    !(listaVeterinarios[i].TELEFONE >= 960000000 && listaVeterinarios[i].TELEFONE <= 969999999)) {
                    printf("O número de telefone deve começar com 2, 91, 93 ou 96. Tente novamente.\n");
                    continue;
                }

                // Verifica se o telefone tem exatamente 9 dígitos
                int num = listaVeterinarios[i].TELEFONE;
                count = 0;

                while (num != 0) {
                    num /= 10;
                    count++;
                }
                if (count != 9) {
                    printf("O número de telefone deve ter 9 dígitos. Tente novamente.\n");
                }
            } while (count != 9);

            printf("\n(Horas antigas: %f) Novas horas: ", listaVeterinarios[i].HORAS_TRABALHADAS);
            scanf("%f", &listaVeterinarios[i].HORAS_TRABALHADAS);

            // Interrompe o loop assim que o veterinário for encontrado e editado
            break;
        }
    }

    if (encontrado) {
        FILE *ficheiro = fopen("veterinarios.txt", "w");
        if (ficheiro == NULL) {
            printf("Erro ao abrir o ficheiro para escrita.\n");
            return;
        } else {
            for (int i = 0; i < num_veterinarios; i++) {
                fprintf(ficheiro, "%d\t%d\t%s\t%s\t%d\t%f\n",
                        listaVeterinarios[i].ID,
                        listaVeterinarios[i].NIF,
                        listaVeterinarios[i].NOME,
                        listaVeterinarios[i].ESPECIALIDADE,
                        listaVeterinarios[i].TELEFONE,
                        listaVeterinarios[i].HORAS_TRABALHADAS);
            }
        }
        fclose(ficheiro);

        printf("Veterinario editado com sucesso!\n");
    } else {
        printf("\nERRO - Veterinario não encontrado!\n");
        return;
    }
}


void MOSTRAINTERVENCOES_IDANIMAL(INTERVENCAO listaIntervencoes[], int num_intervencoes, ANIMAL listaAnimais[], int num_animais)
{
	int id_animal, contador = 0, existe;

	printf("\nDigite o ID do animal que deseja ver: ");
	scanf("%d", &id_animal);
	existe = VERIFICAR_ID_ANIMAL(listaAnimais, num_animais, id_animal);

	if (existe == 1)
	{
		if (listaIntervencoes != NULL)
		{
			if (num_intervencoes > 0)
			{
				int i; // Declaração da variável 'i'
				for (i = 0; i < num_intervencoes; i++) // Loop sobre as intervenções
				{
					if (listaIntervencoes[i].ID_ANIMAL == id_animal)
					{
						printf("%d\t%d\t%d\t%d\t%s\t%s\t%.2f\n",
       					listaIntervencoes[i].ID,
       					listaIntervencoes[i].TIPO_INTERVENCAO,
       					listaIntervencoes[i].ID_VETERINARIO,
       					listaIntervencoes[i].ID_ANIMAL,
       					listaIntervencoes[i].DATA,
      					listaIntervencoes[i].HORA,
      			 		listaIntervencoes[i].CUSTO);
						contador++;
					}
				}
				printf("\nForam encontrados %d registros.\n", contador);
			}
			else
			{
				printf("\nNão existem dados para listar\n");
			}
		}
		else
		{
			printf("\nERRO - Vetor intervenções inválido\n");
		}
	}
	else
	{
		printf("\nERRO - ID do animal não encontrado!\n");
	}
}


void DEVOLVEVALORESGASTOSPOR_IDDONO(DONO listaDonos[], int num_donos, INTERVENCAO listaIntervencoes[], int num_intervencoes, ANIMAL listaAnimais[], int num_animais)
{
	for (int i = 0; i < num_donos; i++)
	{
		float total = 0;
		for (int y = 0; y < num_animais; y++)
		{
			if (listaDonos[i].ID == listaAnimais[y].ID_DONO)
			{
				for (int x = 0; x < num_intervencoes; x++)
				{
					if (listaIntervencoes[x].ID_ANIMAL == listaAnimais[y].ID)
					{
						total += listaIntervencoes[x].CUSTO;
					}
				}
			}
		}
		printf("DONO ID %d - TOTAL -> %.2f Euros\n", listaDonos[i].ID, total);
	}
}
int compararNomesDono(const void *a, const void *b) {
    DONO *donoA = (DONO *)a;
    DONO *donoB = (DONO *)b;
    return strcmp(donoA->NOME, donoB->NOME);
}
void MOSTRARDONOSANIMAISORDEM(DONO listaDonos[], int num_donos) {
    // Ordenar os donos em ordem alfabética pelo nome
    qsort(listaDonos, num_donos, sizeof(DONO), compararNomesDono);

    printf("\nLISTA DE DONOS EM ORDEM ALFABÉTICA\n");
    printf("-------------------------------------------------------------\n");
    printf("ID\tNOME\tCIDADE\tTELEFONE\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < num_donos; i++) {
        printf("%d\t%s\t%s\t%d\n", listaDonos[i].ID, listaDonos[i].NOME, listaDonos[i].CIDADE, listaDonos[i].TELEFONE);
    }
    printf("-------------------------------------------------------------\n");
}



void LISTADONOSANIMAISORDEM(DONO listaDonos[], int num_donos, int num_animais, ANIMAL listaAnimais[]) {
    // Ordenar os donos em ordem alfabética pelo nome
    qsort(listaDonos, num_donos, sizeof(DONO), compararNomesDono);

    printf("\nLISTA DE DONOS E SEUS RESPECTIVOS ANIMAIS EM ORDEM ALFABÉTICA\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < num_donos; i++) {
        printf("\nID Dono %d - Nome: %s\n", listaDonos[i].ID, listaDonos[i].NOME);

        int animaisDoDono = 0;
        for (int j = 0; j < num_animais; j++) {
            if (listaAnimais[j].ID_DONO == listaDonos[i].ID) {
                printf("\t%d\t %s\t %s\t %s\t %c\t %.2f\n", listaAnimais[j].ID, listaAnimais[j].NOME, listaAnimais[j].ESPECIE, listaAnimais[j].RACA, listaAnimais[j].GENERO, listaAnimais[j].PESO);
                animaisDoDono++;
            }
        }

        if (animaisDoDono == 0) {
            printf("\tNenhum animal registado.\n");
        }
    }
    printf("-------------------------------------------------------------\n");
}



int compararNomes(const void *a, const void *b)
{
	return strcmp(((ANIMAL *)a)->NOME, ((ANIMAL *)b)->NOME);
}

void MOSTRARDADOSANIMAISORDEM(ANIMAL animais[], int num_animais)
{

	MOSTRARDADOSANIMAIS(animais, num_animais);
	char especie_desejada[50];
	printf("Espécie desejada: ");
	scanf("%s", especie_desejada);
	capitalize(especie_desejada);
	ANIMAL *animaisDaEspecie = (ANIMAL *)malloc(num_animais * sizeof(ANIMAL));
	int num_animais_da_especie = 0;

	for (int i = 0; i < num_animais; i++)
	{
		if (strcmp(animais[i].ESPECIE, especie_desejada) == 0)
		{
			animaisDaEspecie[num_animais_da_especie] = animais[i];
			num_animais_da_especie++;
		}
	}

	if (num_animais_da_especie == 0)
	{
		printf("Nenhum animal encontrado para a espécie %s.\n", especie_desejada);
		free(animaisDaEspecie);
		return;
	}

	qsort(animaisDaEspecie, num_animais_da_especie, sizeof(ANIMAL), compararNomes);

	printf("\nFORAM ENCONTRADOS %d REGISTOS DE ANIMAIS DA ESPÉCIE %s POR ORDEM ALFABÉTICA\n", num_animais_da_especie, especie_desejada);
	printf("-------------------------------------------------------------\n");
	printf("ID\tNOME\tESPECIE\tRACA\tGENERO\tPESO\tID_DONO\n");
	printf("-------------------------------------------------------------\n");
	for (int i = 0; i < num_animais_da_especie; i++)
	{
		printf("%d\t%s\t%s\t%s\t%c\t%.2f\t%d\n",
							   animaisDaEspecie[i].ID,
							   animaisDaEspecie[i].NOME,
							   animaisDaEspecie[i].ESPECIE,
							   animaisDaEspecie[i].RACA,
							   animaisDaEspecie[i].GENERO,
							   animaisDaEspecie[i].PESO,
							   animaisDaEspecie[i].ID_DONO);
	}
	printf("-------------------------------------------------------------\n");

	free(animaisDaEspecie);
}


void LISTA_INTERVENCOES_INTERVALO(INTERVENCAO listaIntervencoes[], int num_intervencoes, char *data_inicio, char *data_fim)
{
    printf("\nIntervenções no intervalo de tempo de %s a %s:\n", data_inicio, data_fim);
    int encontrados = 0;
	printf("ID\tINT\tVET\tANIMAL\tDATA\t\tHORA\tCUSTO\n");
    for (int i = 0; i < num_intervencoes; i++)
    {
        if (dataEstaNoIntervalo(listaIntervencoes[i].DATA, data_inicio, data_fim))
        {
            encontrados++;
            printf("%d\t%d\t%d\t%d\t%s\t%s\t%.2f\n",
       					listaIntervencoes[i].ID,
       					listaIntervencoes[i].TIPO_INTERVENCAO,
       					listaIntervencoes[i].ID_VETERINARIO,
       					listaIntervencoes[i].ID_ANIMAL,
       					listaIntervencoes[i].DATA,
      					listaIntervencoes[i].HORA,
      			 		listaIntervencoes[i].CUSTO);
        }
    }
    printf("\nTotal de intervencoes encontradas: %d\n", encontrados);
}



int compareDonoGasto(const void *a, const void *b) {
    float gasto_a = *((float *)a);
    float gasto_b = *((float *)b);

    if (gasto_a < gasto_b) return 1;
    if (gasto_a > gasto_b) return -1;
    return 0;
}

void LISTAR_DONOS_POR_VALOR_GASTO(DONO listaDonos[], int num_donos, INTERVENCAO listaIntervencoes[], int num_intervencoes, ANIMAL listaAnimais[], int num_animais) {
    // Criar um array para armazenar o valor total gasto por cada dono
    float valorTotalPorDono[num_donos];

    // Calcular o valor total gasto por cada dono
    for (int i = 0; i < num_donos; i++) {
        float total = 0;
        for (int y = 0; y < num_animais; y++) {
            if (listaDonos[i].ID == listaAnimais[y].ID_DONO) {
                for (int x = 0; x < num_intervencoes; x++) {
                    if (listaIntervencoes[x].ID_ANIMAL == listaAnimais[y].ID) {
                        total += listaIntervencoes[x].CUSTO;
                    }
                }
            }
        }
        valorTotalPorDono[i] = total;
    }

    // Ordenar o array valorTotalPorDono por valor gasto em ordem decrescente
	qsort(valorTotalPorDono, num_donos, sizeof(float), compareDonoGasto);

    // Imprimir a lista de donos por ordem decrescente do valor gasto
    printf("Lista de donos por ordem decrescente do valor gasto:\n");
    for (int i = 0; i < num_donos; i++) {
        printf("[Dono ID %d] - Valor total gasto: %.2f euros\n", listaDonos[i].ID, valorTotalPorDono[i]);
    }
}







//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////MAIN/////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	system("cls");

	setlocale(LC_ALL, "Portuguese");

	ANIMAL animais[MAX_ANIMAIS];
	DONO donos[MAX_DONOS];
	VETERINARIO veterinarios[MAX_VETERINARIOS];
	INTERVENCAO intervencoes[MAX_INTERVENCOES];

	int num_donos;
	int num_animais;
	int num_veterinarios;
	int num_intervencoes;

	int opcao, subopcao;

	char data[11];

	CARREGARDADOSANIMAIS(animais, &num_animais);
	CARREGARDADOSVETERINARIOS(veterinarios, &num_veterinarios);
	CARREGARDADOSDONOS(donos, &num_donos);
	CARREGARDADOSINTERVENCOES(intervencoes, &num_intervencoes);


	// Menu
	do
	{
		printf("\n _______________________________\n");
		printf("|            VetPet+24          |\n");
		printf("|_______________________________|\n");
		printf("| .Menu:                        |\n");
		printf("|                               |\n");
		printf("| 1. Animal e Donos;            |\n");
		printf("| 2. Veterinarios;              |\n");
		printf("| 3. Intervencoes;              |\n");
		printf("| 4. Sair                       |\n");
		printf(" -------------------------------\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);

		switch (opcao)
		{
		case 1:
			printf("\n ___________________________________________________________________\n");
			printf("|                            VetPet+24                              |\n");
			printf("|___________________________________________________________________|\n");
			printf("|.Animal e Donos:                                                   |\n");
			printf("|                                                                   |\n");
			printf("|1. Adicionar Animal;                                               |\n");
			printf("|2. Editar Animal;                                                  |\n");
			printf("|3. Eliminar Animal;                                                |\n");
			printf("|4. Listar Animais e Donos;                                         |\n");
			printf("|5. Listar Donos e respetivos Animais;                              |\n");
			printf("|6. Listar Donos por ordem alfabetica;                              |\n");
			printf("|7. Editar Dono;                                                    |\n");
			printf("|8. Eliminar Dono;                                                  |\n");
			printf("|9. Listar Donos com valor gasto total;                             |\n");
			printf("|10.Listar Animais por ordem alfabetica de uma determinada especie; |\n");
			printf("|0. Voltar atras;                                                   |\n");
			printf(" ___________________________________________________________________\n");
			printf("Escolha uma subopcao: ");
			scanf("%d", &subopcao);
			switch (subopcao)
			{
				system("cls");
			case 0:
				return;
			case 1:
				system("cls");
				ADICIONARANIMAL(animais, &num_animais, donos, &num_donos);
				break;
			case 2:
				system("cls");
				EDITARANIMAL(animais, num_animais,donos, num_donos);
				break;
			case 3:
				system("cls");
				MOSTRARDADOSANIMAIS(animais, num_animais);
				ELIMINARANIMAL(animais, &num_animais);
				break;
			case 4:
				system("cls");
				MOSTRARDADOSANIMAIS(animais, num_animais);
				MOSTRARDADOSDONOS(donos, num_donos);
				break;
			case 5:
				system("cls");
				LISTAANIMAISDONOS(animais, donos, num_animais, num_donos);
				break;
			case 6:
				system("cls");
				MOSTRARDONOSANIMAISORDEM(donos, num_donos);
				break;
			case 7:
				system("cls");
				EDITARDONO(donos, num_donos);
				break;
			case 8:
				system("cls");
				ELIMINARDONO(donos, &num_donos, animais, num_animais);
				break;
			case 9:
				system("cls");
				DEVOLVEVALORESGASTOSPOR_IDDONO(donos, num_donos, intervencoes, num_intervencoes, animais, num_animais);
				printf("\n-----------------------------------------------------------------------------------\n");
				LISTAR_DONOS_POR_VALOR_GASTO(donos, num_donos, intervencoes, num_intervencoes, animais, num_animais);
				break;
			case 10:
				system("cls");
				MOSTRARDADOSANIMAISORDEM(animais, num_animais);
				break;
			default:
				printf("Opcao invalida!\n");
			}
			break;
		case 2:
			printf("\n ________________________________________________________________\n");
			printf("|                           VetPet+24                            |\n");
			printf("|________________________________________________________________|\n");
			printf("| .Veterinarios:                                                 |\n");
			printf("|                                                                |\n");
			printf("| 1. Adicionar veterinario;                                      |\n");
			printf("| 2. Editar veterinario;                                         |\n");
			printf("| 3. Eliminar veterinario;                                       |\n");
			printf("| 4. Listar intervecoes de um veterinario num intervalo de tempo;|\n");
			printf("| 5. Listar veterinarios;                                        |\n");
			printf(" ----------------------------------------------------------------\n");
			printf("Escolha uma subopcao: ");
			scanf("%d", &subopcao);
			switch (subopcao)
			{
				system("cls");
			case 1:
				system("cls");
				ADICIONARVETERINARIO(veterinarios, &num_veterinarios);
				break;
			case 2:
				system("cls");
				EDITARVETERINARIO(veterinarios, num_veterinarios);
				break;
			case 3:
				system("cls");
				ELIMINARVETERINARIO(veterinarios, &num_veterinarios, intervencoes, &num_intervencoes);
				break;
			case 4:
				system("cls");
				printf("\n\t\tMissao em falta de um heroi\n");
				MOSTRAVETERINARIOS(veterinarios, num_veterinarios);
				LISTA_INTERVENCOESVETERINARIO_DATA(intervencoes, num_intervencoes);
				break;
			case 5:
				system("cls");
				MOSTRAVETERINARIOS(veterinarios, num_veterinarios);
				break;
			default:
				printf("Opcao invalida!\n");
			}
			break;
		case 3:
			printf("\n _______________________________________________________________________________________\n");
			printf("|                                     VetPet+24                                         |\n");
			printf("|_______________________________________________________________________________________|\n");
			printf("| .Intervencoes:                                                                        |\n");
			printf("|                                                                                       |\n");
			printf("| 1. Agendar intervencao;                                                               |\n");
			printf("| 2. Listar todas as intervencoes;                                                      |\n");
			printf("| 3. Listar intervencoes por intervalo de tempo;                                        |\n");
			printf("| 4. Consultar historico de intervencoes animal;                                        |\n");
			printf("| 5. Determinar custo total de futuras intervencoes de um animal;                       |\n");
			printf("| 6. Determinar o custo total de todas as futuras intervencoes dos animais de um dono;  |\n");
			printf(" ---------------------------------------------------------------------------------------\n");
			printf("Escolha uma subopcao: ");
			scanf("%d", &subopcao);

			switch (subopcao)
			{
				system("cls");
			case 1:
				system("cls");
				AGENDARINTERVENCAO(veterinarios, num_veterinarios, intervencoes, &num_intervencoes, animais, num_animais);
				break;
			case 2:
				system("cls");
				MOSTRAINTERVENCOES(intervencoes, num_intervencoes);
				break;
			case 3:
			    system("cls");
			    char data_inicio[11], data_fim[11];
			    printf("Insira a data de anterior ao inicio (DD-MM-AAAA): ");
			    scanf("%s", data_inicio);
			    printf("Insira a data posterior ao fim (DD-MM-AAAA): ");
			    scanf("%s", data_fim);
			    LISTA_INTERVENCOES_INTERVALO(intervencoes, num_intervencoes, data_inicio, data_fim);
			    break;
			case 4:
				system("cls");
				MOSTRARDADOSANIMAIS(animais, num_animais);
				MOSTRAINTERVENCOES_IDANIMAL(intervencoes, num_intervencoes, animais, num_animais);
				break;

			case 5:
				system("cls");
				printf("\n\t\t**Nao Implementada corretamente**\n");
				MOSTRARDADOSANIMAIS(animais, num_animais);
				DETERMINARCUSTOTOTALINTERVENCOES_IDANIMAL(intervencoes, num_intervencoes);
				break;
			case 6:
			 	system("cls");
		        int ID;
		        char data_limite[11];
		        MOSTRARDADOSDONOS(donos, num_donos);
		        printf("Insira o ID do dono: ");
		        scanf("%d", &ID);
		        printf("Insira a data limite (DD-MM-AAAA): ");
		        scanf("%s", data_limite);
		        DETERMINARCUSTOTOTALINTERVENCOES_IDDONO(intervencoes, num_intervencoes, ID, data_limite);
		        break;
			default:
				printf("Opcao invalida!\n");
			}
			break;
		case 4:
			printf("A sair...\n");
			break;
		default:
			printf("Opcao invalida!\n");
		}
	} while (opcao != 4);

	return 0;
}
