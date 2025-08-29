/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:28:21 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/29 05:58:04 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Objetivo do push_swap

O push_swap é um projeto do Common Core da 42 cujo objetivo principal é:

  - Ordenar uma lista de inteiros, fornecida como argumento ao programa, utilizando apenas duas
    stacks (stack A e stack B) e um conjunto limitado de operações.

    - Temos inicialmente todos os inteiros na stack A, e a stack B começa vazia.
    - Temos de terminar com todos os números ordenados em ordem crescente na stack A, e a stack B vazia.
    - As únicas ferramentas que podemos usar são as operações definidas pelo projeto (sa, sb, pa, pb, ra,
      rb, rra, rrb, etc.).
    - O grande desafio não é só ordenar, mas fazê-lo com o menor número possível de operações.

O que acontece durante a execução ?

    > Parsing e validação: O programa começa por validar os argumentos: números válidos, sem duplicados, 
                           dentro do range INT_MIN..INT_MAX.

    > Indexação: Cada número é convertido num índice de 0 até N-1, baseado na sua posição ordenada.
                 Exemplo: [42, -5, 100] → índices [1, 0, 2].
                 Isto simplifica as comparações, porque não precisamos de lidar com valores grandes, negativos
                 ou overflow — apenas com “ranks”.

    > Divisão inicial (push para B): Uma parte significativa dos elementos de A é empurrada para B (normalmente
                                     cerca de metade, escolhidos pelos índices mais baixos).
                                     Isto reduz o problema e deixa A com poucos elementos (tipicamente 3).

    > Ordenação de casos pequenos em A: Se A tiver 2 ou 3 elementos, ordena-se diretamente com swaps e rotações 
                                        minimalistas. Isto garante que A já está ordenada localmente.

    > Reinserção inteligente dos elementos de B: De forma iterativa:

        > Para cada elemento em B, calcula-se onde ele deveria entrar em A (posição alvo).
        > Calcula-se o custo da rotação em A e B para alinhar tudo.
        > Escolhe-se sempre o elemento com menor custo total.
        > Executam-se rotações combinadas (rr ou rrr) para poupar operações.
        > Faz-se pa para mover o elemento para A.

    > Ajuste final: Quando todos os elementos estão de volta a A, esta pode não começar no menor índice.
                    Último passo: rodar A até o índice 0 estar no topo → lista final totalmente ordenada.
                    
Algoritmo do meu Push Swap:

    > Turkish (método turco): - Divide os números em blocos (chunks) e empurra para B, por grupos.
                              - Depois traz de volta para A com cálculos de posição.

                              - Indexação dos valores para simplificar a manipulação.
                              - Push_to_b com critério de metade → mandamoss para B cerca de metade dos elementos 
                                de A (os de menor índice). Isto é uma espécie de chunk único.
                              - Ordenação de 3 elementos em A → caso base pequeno.
                              - Reinserção:
                                
                                    - Calculamos target, cost_a e cost_b.
                                    - Procuramos o elemento de B cujo custo de inserção seja mais barato.
                                    - Usamos rotações combinadas (rr/rrr) para reduzir operações.
                                    - Repetimos até B estar vazio.

                               - Shift final da stack A para alinhar o menor índice no topo.


Porquê que é eficiente ? Com a parte do cálculo de custos e rotações combinadas, chegamoss facilmente dentro dos 
                         limites de operações do projeto:
                          
                         ≤ 700 operações para 100 números
                         ≤ 5500 operações para 500 números


No visualizer do push_swap temos: Stack A → aparece no lado esquerdo
                                  Stack B → aparece no lado direito

No início (Count: 0), uma das stacks está cheia e a outra completamente vazia.
Essa stack cheia é a stack A, independentemente de estar à esquerda ou à direita no visualizer.

O que acontece no teu algoritmo

    Início → todos os valores estão em A (esquerda).
    Push inicial (pb) → empurramos metade (ou mais) para B → o lado direito começa a encher de barras.
    Ordenação em A → A fica só com 3 elementos (caso base), ordenados localmente.
    Reinserção (pa) → vamos buscar de volta os elementos de B, um a um, e colocamos no sítio certo em A → o lado direito
                      esvazia e o esquerdo vai ficando ordenado.

🎨 No visualizer

    É normal e esperado veres as barras a “migrar” da esquerda para a direita logo no início (porque usamos pb).
    Mais tarde, durante a reinserção, vais ver o inverso: a stack B esvaziar (direita) e a A organizar-se (esquerda).

POr exemplo, quando iniciamos o push_swap no visualizer, o que observamos no inicio é o estado inicial da stack A com 500 valores aleatórios:

    > Cada barra horizontal representa um valor.
    > O comprimento e a cor correspondem à magnitude do número (normalmente verde/azul para valores baixos e vermelho/amarelo para valores altos).
    > Como ainda não executamos nenhuma operação (Count: 0 está a zero), a stack A aparece toda embaralhada.

Quando carregarmos em Start, o visualizer vai aplicar os comandos gerados pelo push_swap e as barras vão-se mover.

O que se vê no ecrã

    Direita → Stack B (vê-se cheia, em degradê do azul até vermelho).
    Esquerda → Stack A (ainda tem bastantes valores, mas divididos em blocos de cores).
    Comandos (em baixo à direita) → sequência de operações que o teu programa está a executar (rrb, pa, ra, …).
    Count: 4775 → até esse frame já foram feitas ~4775 operações.

O que o algoritmo está a fazer aqui

    Push inicial para B

        No teu algoritmo, empurras cerca de metade dos números (os de menor índice) para B.

        É por isso que B está quase cheia no lado esquerdo.

    Ordenação dos 3 restantes em A

        A fica com 3 elementos, que já são ordenados diretamente (sa, ra, rra).

        Isso já aconteceu mais acima no processo.

    Reinserção gulosa dos elementos de B em A

        Agora o programa está a calcular para cada elemento em B onde ele deve entrar em A, e a mover.

        Os comandos que vês (rrb, pa, ra, etc.) são exatamente isso:

            rrb → roda B para alinhar o próximo elemento.

            pa → move esse elemento para A.

            ra → roda A para colocar esse elemento na posição certa.

    Visualmente

        À esquerda (B), as barras vão-se movendo até irem todas parar em A.

        À direita (A), começa a formar-se o degradê contínuo (ordenado).

        No final, A vai estar do azul (valores mais pequenos) no topo → até ao vermelho (maiores) no fundo.

        B ficará vazia.

📊 Em resumo

O que estás a ver é a fase de reinserção do algoritmo Turkish Greedy que implementaste:

    B cheio (com os elementos de índices mais baixos).

    A ainda não ordenado mas com 3 elementos já fixos.

    O programa está a escolher sempre o elemento de B cujo custo de inserção é menor, depois:

        faz rotações (rrb, ra) para alinhar,

        move (pa),

        e repete.

No fim do processo:
✅ B fica vazio,
✅ A fica totalmente ordenado,
✅ o contador mostra o nº total de operações.



No final, se o algoritmo estiver correto, vais ver as barras alinhadas de cima para baixo em degradé suave, ou seja, ordenadas.




typedef struct s_stack {
	int   value;    // valor original (int)
	int   index;    // rank 0..N-1 após indexação (min->0, max->N-1)
	int   pos;      // posição atual na stack (0 = topo). recalculado várias vezes
	int   target;   // posição em A onde este node deve ser inserido
	int   cost_a;   // custo para alinhar A até 'target' (sinal indica direção)
	int   cost_b;   // custo para alinhar B até 'pos' (sinal indica direção)
	struct s_stack *next;
} t_stack;

1)

int	main(int c, char **args)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**str;

	str = NULL;
	stack_a = NULL;
	stack_b = NULL;
	if (c > 1)
	{
		str = ft_parsing_stack(args);  (1.1)
		ft_parsing(str);               (1.2)
		ft_fill_stack(str, &stack_a);  (1.3)
		free_arr(str);
		ft_index_stack(stack_a, ft_size(stack_a)); (1.4)
		ft_push_swap(&stack_a, &stack_b, ft_size(stack_a));  (1.5)
		ft_free_stack(&stack_a);  (1.6)
		ft_free_stack(&stack_b);
	}
	return (0);
}


a) t_stack *stack_a; e t_stack *stack_b;

    t_stack é um node de uma linked list.
    Linked list = vários nodes encadeados -> cada node guarda dados e um ponteiro para o próximo node.

    Uma linked list é uma estrutura de dados dinâmica onde cada elemento (node) guarda os dados (no caso
    do push_swap guarda o value, o index, o target e outros campos) e guarda um ponteiro para o próximo node 
    na lista.

    Uma linked list é diferente de um array: Num array, os elementos estão todos seguidos em memória.
                                             Numa linked list, cada node pode estar em qualquer sítio da memória,
                                             mas estão encadeados pelos ponteiros.

    No push swap, o node é representado pela struct s_stack.

    Tipo: t_stack é o node da linked list (representa a minha stack).

    typedef struct s_stack 
    {
        int   value;    // o número original do input (ex: 42)
        int   index;    // a posição ordenada (rank 0..N-1)
        int   pos;      // posição atual na stack (0 é o head)
        int   target;   // para onde deverá ir em A
        int   cost_a;   // custo de rodar A até target
        int   cost_b;   // custo de rodar B até o node
        struct s_stack *next; // aponta para o próximo node
    }   t_stack;

    Visualmente, cada node é uma espécie de "caixa":

              NODE (T_STACK) 
     -------------------------------
    | value | index | ... | next -> |
     -------------------------------

    > O next aponta para o próximo node.
    > Se for o último node, next = NULL.

    Cada node tem:

        - value (o inteiro original),
        - index (rank 0..N-1 após indexação),
        - pos, target, cost_a, cost_b (usados durante o algoritmo),
        - next (aponta para o próximo node).

    Como cada t_stack representa um node ?

    Cada número do input transforma-se num node (t_stack) com: > value = número original
                                                               > index = ordem relativa após a indexação
                                                               > outros campos (pos, target, cost_a, cost_b) 
                                                                 vão sendo calculados durante o algoritmo

    E todos os nodes são ligados com next:

    stack_a ──► [ value=4, index=2 ] ──► [ value=-1, index=0 ] ──► [ value=100, index=5 ] ──► NULL

    O que é o head ?

    O head é o primeiro node da lista.
    É ele que guardamos em stack_a ou stack_b.
    Em contexto da stack, é sempre na head que as operações atuam (pa, pb, sa, etc).

    Visualização de 3 nodes na stack (head à esquerda):

    [head] -> [value=3]->[value=10]->[value=7]->NULL
                 ^           ^           ^
               node0       node1       node2

    Aqui o head aponta para o node com value=3, ou seja, para o node0. Esse node aponta para o próximo (node1) e assim por diante.

    O que é o tail ?

    O tail é o último node da lista.
    É aquele cujo next = NULL.
    
    No exemplo acima, o nosso tail é o node2, com value=7, porque depois dele não há mais nada.
    

    Assim, temos que: > t_stack *stack_a: É um ponteiro que aponta para o head da pilha A, ou seja, aponta para
                                          o primeiro node da stack A. Caso esteja vazia, aponta para NULL.
                                     
                      > t_stack *stack_b: É um ponteiro que aponta para o head da pilha B, ou seja, aponta para 
                                          o primeiro node da stack B. Caso esteja vazia, aponta para NULL.

    Porque são pointers ? As operações (ex.: pa, pb, ra, rra, …) alteram o head da stack. Em C, para
    uma função poder alterar o head, passamos o endereço do ponteiro (t_stack **), e dentro da função
    ele pode fazer, por exemplo, *stack = (*stack)->next, etc.

    Inicializar a NULL:

        - Estado inicial válido e explícito: A e B começam vazias.
        - Permite verificações simples (if (!stack) ...).
        - Torna seguro chamar funções que libertam/consultam a stack.
        - Em caso de erro precoce, não corres o risco de fazer free num lixo.

    Ciclo de vida:

        - São preenchidas em ft_fill_stack (a stack A fica com todos os nodes).
        - Durante o algoritmo, pb/pa movem os nodes entre as stacks A e B (ajustando estes ponteiros).
        - No fim, ft_free_stack(&stack_a) e ft_free_stack(&stack_b) libertam tudo.

b) char **str;

    Antes de criarmos a linked list, precisamos de ler os números em texto (string) da linha de comandos do terminal (argv).
    
    Por exemplo, o input pode ser:  ./push_swap "3 2 1"

    Primeiro transformamos tudo numa string única e depois fazemos split em espaços (' ').

    argv = {"./push_swap", "3", "2", "1", NULL}

    Ficamos com: ft_parsing_stack(argv) → ft_split → {"3", "2", "1", NULL}

    Em que: str[0] = "3"
            str[1] = "2"
            str[2] = "1"
            str[3] = NULL

    Tipo: É um array de strings (cada elemento é char * terminado em '\0').

    Significado no projeto: É a forma normalizada dos argumentos da linha de comandos.

        > Em ft_parsing_stack(args): - juntamos todos os argv[1..] numa única string com espaços,
                                     - fazemos ft_split(..., ' '),
                                     - ficamos com str = {"123", "-4", "42", NULL}.

    Porque str = NULL no arranque? 
    
    > Estado inicial seguro: Logo ao arrancar o programa, ainda não temos str alocada. Ao colocar str = NULL, estamos a dizer
                             algo como "ainda não temos nenhuma string alocada, está vazio".
    > Defensive programming: Se houver erro antes de preenchermos (alocarmos) str, e fizermos free_arr(str), a função vai ver 
                             str = NULL e simplesmente não faz nada, ou seja, não há tentativa de libertar memória não alocada.

    Como isso se encaixa no fluxo do main?

    Arranque seguro

    str = NULL;      // ainda não temos strings
    stack_a = NULL;  // A vazia
    stack_b = NULL;  // B vazia

    Se c > 1 (houver argumentos): > str = ft_parsing_stack(args); → aloca e preenche str, criando, por exemplo, str = {"123", "-4", "42", NULL}.
                                  > ft_parsing(str); → valida o formato e duplicados.
                                  > ft_fill_stack(str, &stack_a); → cria os nodes e liga-os (é criada uma linked list); a stack_a deixa de ser NULL.
                                  > free_arr(str); → libertamos as strings (já não precisamos).


1.1) str = ft_parsing_stack(args)

char	**ft_parsing_stack(char **args)
{
	char	**str;
	char	*s;

	s = NULL;
	s = ft_join_args(args);  (1.1.1)   // primeiro junta os argumentos numa única string
	str = ft_split(s, ' ');  (1.1.2)  // divide essa string em vários números
	free(s);                         // liberta a string temporária
	return (str);                   // devolve os números em texto
}


Independentemente como o utilizador escreve os números na linha de comandos do terminal (com aspas, com vários espaços, separados ou juntos),
queremos sempre acabar com um array de "palavras" onde cada palavra é um número em formato de texto.

    Ex.: ./push_swap 3 2 1
    Ex.: ./push_swap "3 2 1"
    Ex.: ./push_swap " 3" 2 "1 "

Todos estes casos devem resultar num array de palavras assim: str = {"3", "2", "1", NULL}

1.1.1) s = ft_join_args(args); 

args é o argv do main, onde args[0] é o nome do programa.

Vejamos:

static char *ft_join_args(char **args)
{
    char *tmp;
    int   i;

    i = 1;                  // começa em 1 pois ignora argv[0] (nome do programa)
    tmp = ft_strdup("");    // começa com string vazia
    if (!tmp)
    {
        ft_error();
        exit(1);
    }
    while (args[i])
    {
        if (ft_has_only_spaces(args[i]))  // se forem "só espaços", rejeita esses argumentos
        {
            ft_error();
            free(tmp);
            exit(1);
        }
        tmp = ft_strjoin(tmp, args[i]);  // junta o argumento atual
        if (!tmp)
        {
            ft_error();
            exit(1);
        }
        tmp = ft_strjoin(tmp, " ");
        if (!tmp)
        {
            ft_error();
            exit(1);
        }
        i++;
    }
    return tmp;
}

[a] if (ft_has_only_spaces(args[i]))

static int	ft_has_only_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

O que é que a função ft_join_args() faz ?

    - Pega nos argumentos da linha de comandos do terminal (argv) a partir do argv[1] (ignorando o args[0]) constrói/concatena
      tudo numa única string com todos os argumentos (números args[1], args[2], ...), separados por um espaço.
    - Valida “só espaços” por argumento com a função ft_has_only_spaces() e, se acontecer, chama ft_error() e termina 
      (evita criarmos palavras vazias).
    - Garante um espaço entre cada argumento (facilita o split a seguir).  
   
    Linha: tmp = ft_strdup("");

    ft_strdup duplica a string (aloca memória e copia os caracteres).
    Aqui duplicamos "", ou seja, uma string vazia (só contém '\0').

    Resultado: É alocada memória para 1 caracter ('\0').
               tmp passa a apontar para "" (string vazia).

    Garante que tmp é sempre uma string válida desde o início.
    Dá segurança porque tmp pode ser libertado sempre que precisarmos, mesmo que não tenhamoss concatenado nada ainda.

    Isto significa que começamos com uma base segura sobre a qual podemos concatenar (ft_strjoin) logo de seguida.

    Linha: tmp = ft_strjoin(tmp, args[i]);

    Junta o conteúdo acumulado (tmp) com o argumento atual (args[i]).

    A ft_strjoin: - Cria a nova string com espaço para len(s1) + len(s2) + 1.
                  - Copia s1 + s2.
                  - Dá free(s1) automaticamente.
                  - Retorna a nova string.

    Por isso: O tmp antigo é libertado dentro do ft_strjoin.
              O tmp passa a apontar para a nova string concatenada.

    Linha: tmp = ft_strjoin(tmp, " ");

    Agora que já juntamos o argumento, vamos acrescentar um espaço de modo a que o próximo número não fique colado 
    ao anterior. Serve para separar os próximos argumentos quando fizermos split.

    Exemplo: Depois do primeiro argumento "42" → "42 ".
             Depois do segundo "7" → "42 7 ".
             Depois do terceiro "-3" → "42 7 -3 ".

    No fim temos uma única string com tudo concatenado e separado por espaços.

    Exemplo1:  ./push_swap 3 2 1

    Antes do loop: tmp = ft_strdup(""); → "" (string vazia).

    Iteração 1: tmp = ft_strjoin("", "3"); → "3".
                tmp = ft_strjoin("3", " "); → "3 ".

    Iteração 2: tmp = ft_strjoin("3 ", "2"); → "3 2".
                tmp = ft_strjoin("3 2", " "); → "3 2 ".

    Iteração 3: tmp = ft_strjoin("3 2 ", "1"); → "3 2 1".
                tmp = ft_strjoin("3 2 1", " "); → "3 2 1 ".

    No fim: tmp = "3 2 1 ".

    
    Exemplo2:

    Juntamos tudo o que o utilizador escreveu (menos o nome do programa).

    Ex.: Para ./push_swap 3 2 1
              
    args = {"./push_swap", "3", "2", "1", NULL}
    ft_join_args(args) → s = "3 2 1 "

    Ex.: Para ./push_swap " 3" 2 "1 "

    args = {"./push_swap", "  3", "2   1", NULL}
    ft_join_args(args) → s = "  3 2   1 "


1.1.2) str = ft_split(s, ' '); 

    Agora, pegamos na string s (que a função ft_join_args() construiu) e dividimos em várias palavras, utilizando
    o espaço ' ' como separador. 
    O resultado é um array em que cada célula é uma “palavra” (número em texto).

    Exemplo A: s = "3 2 1 "
               ft_split(s, ' ') → str = {"3","2","1", NULL}

    Exemplo B: s = "  3 2   1 "
               ft_split(s, ' ') → str = {"3","2","1", NULL}

    (ft_split normalmente ignora múltiplos espaços — não cria palavras vazias)

    Cada número que estava misturado numa frase só, agora vira uma string separada no array str.

    Porque é importante? No push_swap, não podemoss trabalhar diretamente com a string "3 2 1 ".
    
    Temos de ter cada número isolado ("3", "2", "1") para depois: - verificar se são válidos (ft_parsing(str)),
                                                                  - converter em inteiros (ft_fill_stack).

    A função free(s) liberta a string temporária s que já não precisamos.
    Depois de termos dividido em str, podemos libertar (free(s)), porque toda a informação que interessa agora está em str.
    Isto é importante para não deixar memory leaks.
    Se não libertassemos, ficariamos com memória perdida, porque nunca mais vamos usá-la.

    Por fim, devolvemos o array str (return (str)).

    Voltando à main, str = ft_parsing_stack(args) agora guarda a forma normalizada do input: com cada número separado como
    uma string num array, terminado em NULL. 
    O que significa que transformamos os argumentos da linha de comandos num array
    de strings onde cada string é um número separado.

 
1.2) ft_parsing(str); 

void	ft_parsing(char **args)
{
	if (!ft_valid_args(args))  [a]
	{
		free_arr(args);
		ft_error();
		exit(1);
	}
	if (!ft_is_duplicated(args))  [b]
	{
		free_arr(args);
		ft_error();
		exit(1);
	}
}

Depois de str = ft_parsing_stack(args); temos str como um array de strings, por ex.: {"3", "2", "1", NULL}

Chamamos ft_parsing(str) para garantir que o formato de cada palavra (número em texto) é válido e se não existem números repetidos
(numericamente iguais).

Primeiro verificamos se os argumentos são válidos: 

[a] if (!ft_valid_args(args)) 

static int	ft_valid_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])  // enquanto houver argumentos
	{
		j = 0;
		if (ft_is_signed(args[i][j]))  // verificar se na primeira posição está o sinal '+' ou '-'
		{
			if (!args[i][j + 1])  // verificar se só tem sinal sem número (o que é inválido)
				return (0);
			j++;
		}
		while (args[i][j])  // Percorremos a string caracter a caracter
		{
			if (!ft_is_digit(args[i][j]))  // Verificamos se é digito. Qualquer argumento não numérico é inválido
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


> A função ft_valid_args(args) valida a forma textual de cada string (args[i]) (a string é o array que veio da função
  ft_parsing_stack() e foi criado pela função ft_split()).

> args[i] é uma das strings que veio do ft_split, ou seja, um dos números de input.

> if (ft_is_signed(args[i][j]))  // verifica se na primeira posição está o sinal '+' ou '-'

  ft_is_signed(args[i][j]) verifica se o primeiro carácter é '+' ou '-'.

  Exemplo: args[i] = "-42" → args[i][0] = '-' → ft_is_signed('-') = true.

           args[i] = "123" → args[i][0] = '1' → não é sinal, logo false.

> Se houver sinal, ou seja, se o primeiro carácter for sinal (+ ou -), verificamos se
  existe algum carácter a seguir ao sinal -> if (!args[i][j + 1]) 

  Se não existir (ou seja, se for '\0' → fim da string), significa que o argumento era só "+" ou "-".
  Isso é inválido → porque não há número nenhum.
  Então return (0); → invalida o argumento.

> Se havia sinal e também há mais caracteres depois dele, avançamos o índice j (j++) para começar a 
  verificar a partir do primeiro dígito.

  Exemplo: args[i] = "-42"

           args[i][0] = '-' → sinal.

           args[i][1] = '4' → existe algo depois.

           Fazemos j++, então agora vamos começar a verificar a partir do '4'.
           
> j é o indice dentro da string args[i] -> args[i][j].
  Se havia sinal, começamos em j = 1.
  Se não havua sinal, começamos em j = 0.

> while (args[i][j]) percorre a string caracter a caracter até chegar ao fim da string.

> if (!ft_is_digit(args[i][j])) verifica se o carácter atual é um dígito (0 a 9).
  
  Se não for, retorna 0 → inválido.
  Isso elimina coisas como: "12a" (porque 'a' não é dígito).
                            "3.14" (o '.' reprova).
                            " 42" (o espaço reprova, mas na prática espaços já tinham sido tratados pelo split).
                            
> Se for digito, avança para o próximo caracter (j++).

> Quando terminarmos de validar a string inteira (args[i]), passamos para o próximo argumento (i++).
  O while exterior - while (args[i]) - repete o mesmo processo para todas as strings.

> Por fim, se todos os argumentos tiverem um formato válido, a função retorna 1.

O que garante no fim ?

Depois deste loop: - Cada string (args[i]) foi confirmada como número inteiro válido.
                   - Portanto, no fim de ft_valid_args, todos os elementos de args são strings compostas só por 
                     dígitos (com sinal opcional no início).

                     
O que isto permite: "123", "-7", "+42", "0005", "-0" → válidos
                    Um sinal só no início, e ao menos um dígito a seguir.

O que reprova (exemplos): "" (string vazia)
                          "3.14"
                          "+" ou "-" (sinal sem dígitos)
                          "12a", "--1", "+-3"
                          " 3" (espaços dentro da palavra)
                          "3 2" dentro do mesmo elemento (sem aspas no shell)

Nota: espaços a mais foram resolvidos antes (no split). Se o utilizador pôs tabs ou outros caracteres
      dentro das aspas, aqui vão reprovar por não serem dígitos.

      
Depois de verificarmos com a função ft_valid_args(args):

if (!ft_valid_args(args))
	{
		free_arr(args);
		ft_error();
		exit(1);
	}

Verificamos se alguma das strings não cumprem com as regras impostas pela função ft_valid_args(), ou seja, se após o sinal 
(se existir) todos os caracteres não forem digitos, é libertada a memória do array de strings (args), chama a função
ft_error() para imprimir a mensagem de erro e termina imediatamente o programa com o código de saída 1.

Porque libertamos antes de sair? 

args (isto é, str) foi alocado na função ft_parsing_stack().
Se for inválido, não voltamos à main para não vazar memória, pelo o que libertamos antes de sair com exit(1).

> if (!ft_is_duplicated(args)): Caso as strings cumpram as regras impostas pela função ft_valid_args(), verificamos se há 
  números que se repetem, pois no push swap, a stack inicial não pode ter números repetidos (duplicados).

  Por exemplo: ./push_swap 3 5 2 5

               Aqui o 5 aparece duas vezes, o que torna o input inválido.
    
[b]

int	ft_is_duplicated(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])  // Percorre cada argumento (cada número)
	{
		j = i + 1;
		while (args[j])
		{
			if (ft_atoi(args[i]) == ft_atoi(args[j]))  // compara args[i] com os seguintes
				return (0);   // se encontrou dois números iguais (duplicados) retorna 0 pois é inválido
			j++;  // Se não encontrou duplicados, incrementa para o argumento seguinte e compara com args[i]
		}
		i++; // se o argumento args[i] não é igual a nenhum args[j], avança para o próximo para continuarmos a verificar os seguintes argumentos
	}
	return (1);  // se percorreu tudo sem encontrar números duplicados, retorna 1
}

O objetivo da função ft_is_duplicated() é o de garantir que não existem números repetidos no input.
Compara o valor numérico, não a string em si, ou seja:

  - "1" e "01" → ambos dão 1 em ft_atoi → conta como duplicado.
  - "0" e "-0" → ambos dão 0 → duplicado.

Porque comparamos o valor numérico e não as strings?

Duas strings diferentes podem representar o mesmo número. Exemplos:

String A	 String B	São o mesmo número?	   Comparar como string	           Comparar como número
  "1"	       "01"	       Sim (ambas 1)	    diferentes → falso negativo	         iguais ✅
  "0"	       "-0"	       Sim (ambas 0)	    diferentes → falso negativo	         iguais ✅
 "+42"	       "42"	       Sim (ambas 42)	    diferentes → falso negativo	         iguais ✅

Se comparassemos diretamente as strings (ft_strcmp), iriamoss deixar passar duplicados (ex.: "01" e "1").
Quando convertemos para int (ft_atoi), ambas as representações tornam-se no mesmo valor numérico — e aí o
duplicado é detetado.

Como a função ft_is_duplicated() procura os duplicados?

Vejamos, por exemplo, o array de strings args ->  args = {"10", "-3", "10", "00010", NULL}

A função:

> Começa em i = 0 → ou seja, começamos em "10"

> No loop while (args[i]) vamos percorrer cada argumento até ao fim.

> Para cada argumento (args[i]), começamos j com o próximo elemento (i + 1) -> neste caso j = 1, que corresponde
  a "-3".
  Iniciamos j = i + 1 para assim compararmos args[i] com todos os argumentos seguintes, evitando comparar consigo
  próprio e evitando comparar o mesmo par duas vezes.

> No loop while (args[j]) vamos percorrer os elementos seguintes ao argumento atual, até ao fim.

> if (ft_atoi(args[i]) == ft_atoi(args[j])): Convertemos ambas as strings para um inteiro com ft_atoi e vamos comparar
  os valores numéricos.

  i = 0 e j = 1 → compara "10" com "-3" → 10 != -3 → segue
  i = 0 e j = 2 → compara "10" com "10" → 10 == 10 → ENcontrou um duplicado → retorna 0 (não continua)

(nem precisamos de ver "00010")-

> Se encontrarmos dois números com o mesmo valor numérico, o input é considerado inválido, pois duplicados não são permitidos
  no push swap. A função termina imediatamente retornando 0.

> Ao chegarmos ao fim sem encontrarmos números duplicados, retornamos 1.


Até aqui já fizesmos: > str = ft_parsing_stack(args); → temos um array de strings com cada número em texto,
                        p.ex: str = {"3","-1","2",NULL}
                      > ft_parsing(str); → garantimos que cada string tem formato válido (sinal opcional + dígitos)
                        e não existem repetidos (numericamente).

Falta garantir que cabem num int e transformar estas strings em nodes da stack A. É exatamente isso que faz ft_fill_stack.

1.3)

void	ft_fill_stack(char **str, t_stack **stack)
{
	long int	value;
	int			i;

	*stack = NULL;  // começa com a stack vazia
	i = 0;
	while (str[i])  // percorre cada string 
	{
		if (ft_valid_number(str[i]) == 1)  [a]
		{
			free_arr(str);
			ft_error();
			ft_free_stack(stack);
			exit(1);
		}
		value = ft_atoi(str[i]); // converte para int
		ft_lst_add_back(stack, ft_lst_new(value));  [b]  // cria o node e liga-o no fim 
		i++;
	}
}


> char **str é o array de strings que contém cada número str = {"3", "-1", "42", NULL};
 
  Ou seja:  str[0] → "3"
            str[1] → "-1"
            str[2] → "42"
            str[3] → NULL (fim do array)

> t_stack **stack é o pointer que aponta para o head da stack. É double pointer porque queremos modificar o ponteiro original
  da main, e por isso temos de passar o endereço dela -> ft_fill_stack(str, &stack_a);

> long int value é a variável onde guardamos cada número convertido para inteiro.
  Porquê que é long int ? O push swap só permite inteiros de 32 bits (int → [-2147483648, 2147483647]), mas ao converter de 
  char * (string) para um número (int), precisamos de ter cuidado com o overflow.


> while (str[i]): percorremos as strings (números em texto)

  O str vem do ft_split, termina em NULL.
  Vamos tratar de cada string e transformá-la num node.
  
  Exemplo de input: str = {"3","-1","2",NULL}

> if (ft_valid_number(str[i]) == 1) — verificação do range de um int.

[a]

int	ft_valid_number(const char *str)
{
	long	res;
	int		i;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
		if ((res * sign) > 2147483647 || (res * sign) < -2147483648)
			return (1);
	}
	return (0);
}

A função ft_valid_number() lê o número acumulando em long e devolve 1 se o valor sair do intervalo do int (INT_MIN..INT_MAX).
Aqui completamos a validação: não aceitamos coisas como "2147483648" ou "-2147483649".

Se for inválido: - free_arr(str); → libertamos o array de strings (já não vamos usá-lo).
                 - ft_error(); → escrevemos a mensagem Error\n.
                 - ft_free_stack(stack); → se já tinhamos criado alguns nodes, libertamos para não haver leaks.
                 - exit(1); → aborta e sai.

Após passar pela validação:

> COnvertemos a string para um inteiro (convertemos para o seu valor numérico) -> value = ft_atoi(str[i])

  str[i] = "0005" → value = 5
  str[i] = "-0" → value = 0
  str[i] = "+42" → value = 42

> Criamos e anexamos o node -> ft_lst_add_back(stack, ft_lst_new(value))

    > ft_lst_new(value)

    [b]
    t_stack	*ft_lst_new(int value)
    {
	    t_stack	*new;

	    new = malloc(sizeof(t_stack));
	    if (!new)
		    return (NULL);
	    new->value = value;  // número inteiro original que lêmos do input
	    new->index = 0;      // ainda não indexado (vai receber 0 a n - 1 na função ft_index_stack())
	    new->pos = -1;       // posição atual do node na stack (0 = topo) - ainda não calculada - só é valido em ft_position()
	    new->target = -1;    // posição alvo na stack A onde este node (vindo de B) deve ser inserido para manter A ordenada - ainda não calculada
	    new->cost_a = -1;    // custo do número de rotações que temos de fazer em A para alinhar o target e trazer o node para o topo - ainda não calculada - ft_cost
	    new->cost_b = -1;    // custo do número de rotações que temos de fazer em B para alinhar o target até o node - ainda não calculada
	    new->next = NULL;    // é o ponteiro para o próximo node da linked list - incialmente ainda não está ligado a nenhum node
	    return (new);
    }

    Aloca um t_stack (node) e preenche os campos iniciais:

        - node->value = value;
        - node->index = 0 (ainda não indexado. Será preenchido na função ft_index_stack()).
          Após a função ft_index_stack(), o menor valor terá index = 0 e o maior index = n - 1.
          Inicialmente utilizamos index = 0 como "ainda não indexado".
        - node->pos = node->target = node->cost_a = node->cost_b = -1; (valores “não calculados”)
        - node->next = NULL;

        
    > ft_lst_add_back(stack, ft_lst_new(value))

    void	ft_lst_add_back(t_stack **stack, t_stack *new)
    {
	    t_stack	*last;  // ponteiro que aponta para o último node atual da lista -> guarda o endereço do tail

	    if (!new)   // se a criação do node falhou
		    return ;  // não fazemos nada
	    if (!*stack)  // Se a linked list estiver vazia, não há fim para procurar (o novo node será o primeiro)
	    {
		    *stack = new;  // altera o head, e o novo node torna-se o head
		    return ;  // terminamos
	    }
	    last = ft_last(*stack);  // Percorremos a lista até encontramos o último node (tail) e guardamos em last
	    last->next = new;        // ligamos o novo node ao fim da lista
    }

    A função ft_lst_add_back() anexa o novo node ao fim (tail) da linked list, cujo o head é o *stack.

    Pensemos na linked list como uma fila de caixas ligadas por setas:  head ──► [3] ──► [-1] ──► [2] ──► NULL

    Queremos pôr a nova caixa [7] no fim:  head ──► [3] ──► [-1] ──► [2] ──► [7] ──► NULL

    
    Por que t_stack **stack (ponteiro para ponteiro) ?
    
    > *stack é ponteiro que aponta para o primeiro node (é o head da lista).
    > Às vezes precisamos de alterar o head, por exemplo, quando a lista está vazia (*stack == NULL) e precisamos de anexar
      o primeiro node. 
      Assim, para anexar o primeiro node temos de alterar o head de NULL para o novo node.
    > Para uma função conseguir modificar a variável do chamador (o head), temos de receber o endereço dessa variável -> t_stack ** .
    > Se fosse t_stack *stack (uma cópia), dentro da função faziamos stack = new mas o chamador não veria a mudança, estavamos a
      mudar só a cópia local.
      Assim, como dentro da função fazemos *stack = new, se fizemos sem o ** (se fosse t_stack *stack) alteravamos apenas uma cópia local 
      do ponteiro, e o chamador não veria a mudança.

    O que representa a t_stack *last ?

    > É um ponteiro temporário que aponta para o último node atual da lista, antes de anexarmos o novo.
    > É utilizado para chegarmos ao último node da lista (o tail) sem perder o head.
    > Se fizessemos *stack = (*stack)->next para andar pela lista, perderiamos o head.
      Ao usar um ponteiro temporário, podemos percorrer a lista à vontade.
    > Serve, assim, para conseguirmos fazer last->next = new sem perdermos o head.
    

    O que ft_lst_add_back faz :

    > Lista vazia ? (*stack == NULL) → Quando a lista está vazia, não há fim para procurar: o novo node será o primeiro, passando, assim,
      a ser o head - *stack = new - alteramos assim o head do chamador (por isso precisamos de t_stack **).
      Depois disto, a lista fica: head -> [new] -> NULL.

      Exemplo: *stack = NULL
               new = [7] -> NULL

      if (!*stack) → é verdade
        *stack = new;
    
      Depois:   *stack ──► [7] -> NULL  (head passou a ser [7])

      
    > Caso contrário, percorremos a lista a partir do head até encontrar o node cujo next == NULL. 

      t_stack	*ft_last(t_stack *stack)
      {
	    while (stack && stack->next)  // percorre a lista enquanto houver próximo (stack->next)
		    stack = stack->next;
	    return (stack);    // retorna o primeiro com next == NULL (que é o tail)
      }

      Exemplo: stack = [3] -> [-1] -> [2] -> NULL

               loop:

                stack = [3], stack->next existe → stack = [-1]
                stack = [-1], stack->next existe → stack = [2]
                stack = [2], stack->next == NULL → sai
                
                return [2]

      Exemplo:  Antes: *stack ──► [3] -> NULL
                        new = [7] -> NULL

                if (!*stack) → falso

                last = ft_last(*stack) → last = [3]
                last->next = new;
                
                Depois:  *stack ──► [3] -> [7] -> NULL

      Encontramos o último node (ft_last) e ligamos o novo node ao fim: last->next = new;

      
    Antes:  *stack -> [3] -> [-1] -> [2] -> NULL     Depois: *stack -> [3] -> [-1] -> [2] -> [7] -> NULL
        
            new: [7] -> NULL


    
1.4) ft_index_stack(stack_a, ft_size(stack_a))

void	ft_index_stack(t_stack *stack_a, int size)
{
	t_stack *current;       // ponteiro para percorrer a lista
	t_stack *high_node;      // ponteiro para guardar o endereço do node que contém o maior valor encontrado até agora (maior node ainda sem índice).
	int      max_val;       // guarda o maior valor atual visto 

	while (size-- > 0)   // percorre N vezes (N = tamanho da lista ou seja, N = número de nodes)
	{
		current = stack_a;  // recomeça no ínicio da lista
		high_node = NULL;    // ainda não escolhemos o maior node atual desta iteração
		max_val = INT_MIN;  // o maior valor visto começa no minimo possivel
		while (current)     // percorre a lista inteira
		{
            // só nos interessa os nodes que ainda não têm indice atribuido
			if (current->index == 0 && current->value >= max_val)
			{
				max_val = current->value;   // atualizamos o maior valor visto
				high_node = current;         // guarda o endereço desse node
			}
			current = current->next;  // avançamos na lista para o próximo node
		}
		if (high_node)  // ao percorrermos a lista, se "max_node" é o maior ainda sem indice
			high_node->index = size;  // atribuimos o indice atual (descrescente)
	}
}

Esta função atribui um índice ordenado a cada node da lista stack_a, de modo a que cada node
passa a ter um indice de 0 a N-1 (0 = menor valor da lista, N-1 = maior valor da lista e os restantes valores
ficam no meio por ordem crescente).
Tabalhar com estes indices é muito mais simples no push swap do que utilizar os valores reais (que podem ser 
negativos, muito grandes, etc), Depois disto, quase tudo no algoritmo do push swap compara indices.

A função faz uma espécie de selection sort de máximos: em cada iteração escolhemos o maior node que ainda não
tem índice e damos-lhe o maior índice disponível.
O while (size-- > 0) faz com que os índices atribuídos sejam: N-1, N-2, ..., 0 (nesta ordem).
Como todos os nodes começam com index = 0, cada vez que “marcamos” um node com outro valor (>0), ele deixa de 
ser considerado nas iterações seguintes.
No fim, vai sobrar exatamente um node com index == 0: o menor da lista (é isso mesmo que queremos).

Por que index == 0 significa “ainda não indexado”?

> Em ft_lst_new metemos index = 0 por defeito.
> Nesta função, cada vez que escolhemos um node, mudamos-lhe o index de 0 para N-1, depois N-2, …
> O último node que sobrar sem ser "marcado" (continua 0) é precisamente o menor valor, que no fim deve mesmo 
  ter index = 0.

Exemplo: Suponhamos que a lista tem estes value (na ordem em que foram lidos) e size = 4:

         stack_a:  [  40 ] → [  -5 ] → [ 12 ] → [ 7 ] → NULL
           index:     0         0        0        0


> stack_a: head da lista com todos os nós já criados na função ft_fill_stack().
> size: tamanho atual da lista (usa ft_size(stack_a) ao chamar).
> current: ponteiro para percorrer a lista do ínicio ao fim.
> max_node: ponteiro para guardar o endereço do node que contém o maior valor encontrado até agora (maior node ainda sem índice).
> max_val: valor do “maior valor encontrado até agora” nesta iteração. Serve de referencia para comparar cada node da lista.

Loop while(size-- > 0)

> Este loop executa exatamente N iterações (N = número de nodes).
> A cada iteração é escolhido o node com o maior valor encontrado (ainda sem indice) e atribuimos um índice com max_node->index = size.

  - 1.ª iteração: o maior valor absoluto recebe index = N-1.
  - 2.ª iteração: o 2.º maior recebe index = N-2.
                        …
  - última iteração: o menor recebe index = 0.

  - Isto cria uma compressão ordenada (ranking) 0..N-1, onde 0 é o menor e N-1 o maior.

  
Inicialização: current = stack_a;
		       max_node = NULL;
		       max_val = INT_MIN;

> Recomeçamos no ínicio da lista (current = stack_a). Como current é o ponteiro para percorrer a linked list do inicio ao fim
  (percorre cada node um a um) a cada iteração externa - while(size-- > 0) - vamos voltar a percorrer toda a lista à procura do 
  próximo maior valor.
  Por isso, fazemos sempre current = stack_a para recomeçar novamente no head da lista.
  COmo vamos ver, depois disso fazemos while(current) e vamos avançando com current = current->next até chegar ao fim (NULL).
  QUando acabamos de percorrer a lista à procura do próximo maior valor, voltamos ao íncio para procurarmos o próximo.

  Exemplo: Lista 40 → -5 → 12 → 7

           1ª iteração: current começa em 40 → percorre tudo.
           2ª iteração: voltamos a pôr current = stack_a → começa de novo em 40 → percorre tudo outra vez.

           Isto repete-se N vezes.

> Ainda não temos/encontramos o maior node (max_node == NULL).
  Como max_node guarda o endereço do node que contém o maior valor encontrado até agora (nesta iteração do loop), inicialmente,
  ele é NULL porque ainda não analisamos nenhum node.
  Durante o loop, cada vez que encontrarmos um valor maior do que o atual max_val, fazemos max_node = current.
  Assim, max_node guarda o endereço do node que tem esse maior valor (max_val).

  Exemplo: Na lista 40 → -5 → 12 → 7
  
           1ª iteração: começa max_node = NULL
                        vê 40 → max_node = (node do 40)
                        vê -5 → não muda
                        vê 12 → não muda
                        vê 7 → não muda

           fim: max_node aponta para o nó do 40.
  
> O maior valor visto (max_val) começa no menor possível (INT_MIN) para garantir que qualquer valor da lista (value) será maior
  ou igual (>=) a este logo na primeira comparação. Exemplo: se o 1º node for -50, ele ainda assim é maior que INT_MIN → logo substitui.
  Se começassemos em 0, perderiamos números negativos (ex: numa lista só de negativos, nenhum seria maior que 0 e max_node ficava errado).
  Usar >= em vez de > aqui não muda nada no projeto, porque já garantimos que não há duplicados.
  (Se houvesse dois valores iguais, acabariamos por escolher o último que aparece na lista — o que também seria aceitável.)
  Assim, max_val compara e guarda o maior valor encontrado até agora.
  Como vamos ver, durante o loop, cada vez que vemos um current->value maior do que max_val, atualizamos:

  max_val  = current->value;
  max_node = current;

> No fim do loop: - max_node aponta para o node com o maior valor ainda sem índice.
                  - max_node->index = size; atribui-lhe o índice correto.

                  Depois a próxima iteração repete tudo, mas agora esse node já não entra (porque index != 0).

Loop while (current)

> Vamos percorrer a linked list stack_a do ínicio ao fim.
> O loop termina quando chegamos ao fim da lista (NULL).
> Verificamos se : - current->index == 0 → só consideramos nodes que ainda não receberam um indice. 
                     No início, todos os indices são 0 (definido na função ft_lst_new.
                     Cada vez que atribuimos um indice a um node (max_node->index = size), esse node deixa de ser 0 e será
                     ignorado nas iterações seguintes.
                   - current->value >= max_val → comparamos o valor atual (value) da lista com o maior valor encontrado até 
                     agora (max_val).
                     Se for maior ou igual, significa que encontramos um novo candidato a maior número desta iteração, pelo 
                     o que atualizamos.
                     O >= aqui não muda nada em inputs válidos (não temos duplicados), mas não faz mal: se houvesse duplicados,
                     ficaria com o último.
                     
> Atualização do maior valor visto (max_val)

  Se a condição for satisfeita, atualizamos max_val (max_val = current->value), pelo que agora este é o novo maior valor encontrado.
  
  Exemplo: Antes: max_val = -2147483648 (INT_MIN)
           Current: 40
           Depois: max_val = 40.

  De seguida, guardamos o endereço do node que tem esse valor (max_node = current), assim sabemos quem é o maior node desta iteração.
  Isto serve para quando o loop acabar, fazermos max_node->index = size para atribuirmos o indice correto.

> Avançar para o próximo node da lista (current = current->next)
                     
> Atribuição do índice:

  if (max_node)
            max_node->index = size;

  Durante o loop interno encontramos o maior valor visto até agora entre os nodes com index == 0 (max_val) e guardamos o endereço desse 
  node (ainda sem indice) em max_node.
  Começamos por verificar se a lista tem pelo menos um node ainda sem índice, no final do loop, max_node não é NULL - if (max_node).
  
   Se encontramos o maior node (max_node), atribuimos a ele um indice (index = size).
   Dentro deste while (size-- > 0), o size já foi decrementado:
   
      - 1ª vez: size é N-1 → o maior recebe N-1.
      - 2ª vez: size é N-2 → o 2º maior recebe N-2.
                        …
      - última vez: size é 0 → o menor recebe 0.

    Exemplo: stack_a com valores: [ 40, -5, 12, 7 ], N=4.

    Iteração 1 (size = 3): percorre -> maior sem índice = 40 -> index(40) = 3

    Iteração 2 (size = 2): sem índice: -5, 12, 7 → maior = 12 -> index(12) = 2

    Iteração 3 (size = 1): sem índice: -5, 7 → maior = 7 -> index(7) = 1

    Iteração 4 (size = 0): sem índice: -5 -> index(-5) = 0

    Resultado final (value → index): [40(3)] → [-5(0)] → [12(2)] → [7(1)]


   Porquê que esta função é importante no push_swap ?

   > Depois de ft_index_stack, o algoritmo passa a trabalhar com o indice em vez do value.
   > Em ft_push_to_b, empurramos para B os elementos com indice menor/num intervalo, o que define os “chunks”.
   > O cálculo do target (onde inserir em A) compara índices, não valores → mais direto, sem lidar com negativos, limites, etc.
   > O cálculo de cost_a/cost_b também é guiado por pos/index, e as rotações combinadas são decididas a partir disso.


1.5) ft_push_swap(&stack_a, &stack_b, ft_size(stack_a)); 

static void	ft_push_swap(t_stack **stack_a, t_stack **stack_b, int size)
{
	if (size == 2 && !ft_is_sorted(*stack_a))  [a]
		ft_sa(stack_a);  [b]
	else if (size == 3 && !ft_is_sorted(*stack_a))
		ft_sort_three(stack_a); [c]
	else if (size > 3 && !ft_is_sorted(*stack_a))
		ft_sort(stack_a, stack_b);  [d]
}

Na função ft_push_swap(), escolhemos a estratégia de ordenação conforme o tamanho e só é executado se ainda não estiver ordenado.

Vejamos primeiro como funciona a função ft_is_sorted():

[a] 

int	ft_is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

Esta função verifica se a stack A já se encontra ordenada (em ordem crescente) do topo para a base, ou seja, estar ordenada 
significa que cada node tem um value inferior ou igual (<=) ao value do node seguinte. A verificação aqui é por valor e não
por indice.
Como no push swap não há números duplicados, na prática a ordem é estritamente crescente.

A função recebe o head da linked list t_stack.

> while (stack && stack->next)
  
  Vamos percorrer a lista par a par (node atual vs. próximo node).
  A condição garante que há um próximo node para comparar. Evita NULL->value.
  Se a lista estiver vazia (stack == NULL) ou tiver um só node (stack->next == NULL), o while não entra → não existem quebras 
  → retorna 1 no fim (correto: listas de 0/1 elemento estão “ordenadas”).

  > if (stack->value > stack->next->value) 
        return (0)

    Verifica se há uma inversão: “o valor do node atual é maior do que o valor do próximo node ?”
    Se sim, encontrou uma ordem decrescente naquele par → não está ordenado → devolve 0 imediatamente.
    Caso contrário, continua e ignora este if.
    
  > stack = stack->next: Avança para o node seguinte e repete a comparação com o node seguinte a ele.

  > return (1): Se percorreu todos os nodes sem encontrar value > next->value, então está ordenada → devolve 1.



No ínicio da função ft_push_swap() vamos começar por verificar se a stack A tem exatamete dois nodes (size == 2) e 
se ela não se encontra ordenada em ordem crescente (!ft_is_sorted(*stack_a)).

> if (size == 2 && !ft_is_sorted(*stack_a))
    ft_sa(stack_a);

  Se só temos 2 números e não estão ordenados, apenas um único swap (sa) resolve (trocar os dois do topo).

  [b]

   void	ft_sa(t_stack **stack_a)
   {
	   ft_swap(*stack_a);
	   ft_putstr_fd("sa\n", 1);
   }

   static void	ft_swap(t_stack *stack)
   {
	  int	temp;

	  if (!stack || !stack->next)  // se tivessemos menos de 2 nodes não havia nada para trocar
		  return ;
      // trocar os "values"
	  temp = stack->value;
	  stack->value = stack->next->value;
	  stack->next->value = temp;
      // trocar os "indices"
	  temp = stack->index;
	  stack->index = stack->next->index;
	  stack->next->index = temp;
   }

   Porque que trocamos também os indices ?

   Porque index é o rótulo do valor (rank). Se trocassemos só os value, ficavamos com pares incoerentes (o node com
   value = 1 mas index que pertencia ao 2). Trocando os dois campos, é como se tivessemoss “trocado os nodes” sem
   mexermos em next — o par (value, index) continua coerente.


> else if (size == 3 && !ft_is_sorted(*stack_a))
    ft_sort_three(stack_a);

  Se temos 3 números e a stack não está ordenada -> usamos o algortimo fixo para três elementos (ft_sort_three).

  void	ft_sort_three(t_stack **stack_a)
  {
	  int	high;

	  if (ft_is_sorted(*stack_a))        // se já estiver ordenada
		  return ;                        // sai
          
	  high = ft_find_high(*stack_a); [c2]   // encontra o maior value na stack A
      
	  if ((*stack_a)->value == high)   // verifica se o maior value está no topo
		  ft_ra(stack_a); [c3]         // se sim, manda-o do topo para a base -> o maior vai para a base
	  else if ((*stack_a)->next->value == high)  // verifica se o maior está no meio
		  ft_rra(stack_a); [c4]             // se sim, desloca o que está na base para o topo -> o maior desliza para a base
	  if ((*stack_a)->value > (*stack_a)->next->value)  // verifica se os dois de cima (topo e o meio) estão desordenados
		  ft_sa(stack_a);  [c5]           // se estiverem, troca-os para obtermos topo < meio
  }

  A função ft_sort_three() ordena a stack A (do topo para a base), em ordem crescente, com o minimo de operações.

  Imaginemos a stack A:

  Topo (head)  →  [a]  →  [b]  →  [c]  →  NULL  =  Base (fundo)
                   ^topo   ^meio   ^base

   As operações usadas: - sa → troca os dois do topo ([a] com [b]).
                        - ra → roda para cima: o topo vai para a base  ->  [a, b, c] → ra → [b, c, a]
                        - rra → roda para baixo: a base vem para o topo.  ->  [a, b, c] → rra → [c, a, b]

   A ideia é pôr o maior na base com 1 rotação (ra ou rra) e depois, se os dois de cima estiverem desordenados, fazer 1 swap (sa).
   Com isso ficamos com a stack A ordenada, do topo para a base [menor, médio, maior].
                                                                   ^topo  ^meio  ^base

   Como isto funciona sempre ? Com 3 elementos, há só 6 ordens possíveis em que em todas elas:

        > com um rotate ou reverse rotate (ra ou rra) conseguimos colocar o maior na base.
        
              [a, b, c] → ra → [b, c, a]   ou   [a, b, c] → rra → [c, a, b]

        > se os dois de cima (o topo e o meio) estiverem desordenados (topo > meio), trocamos eles com o swap (sa).
        
    Utilizamos assim no máximo duas operações.

    A função ft_sort_three() precisa de saber onde está o maior dos três para decidir que rotação fazer:

        - se o maior está no topo → ra (o topo vai para a base)  ->  [a, b, c] → ra → [b, c, a]
        - se o maior está no meio → rra (a base vai para o topo, empurrando o meio para a base)  ->  [a, b, c] → rra → [c, a, b]
        - se não está no topo nem no meio, então está na base → não roda.

        
    Vejamos como vamos descobrir o maior value que existe na stack A, com a função ft_find_high() :
                                 
    [c2] high = ft_find_high(*stack_a);

    int	ft_find_high(t_stack *stack)
    {
	    int	high;

	    high = INT_MIN;
	    while (stack)
	    {
		    if (stack->value > high)
		  	    high = stack->value;
		    stack = stack->next;
	    }
	    return (high);
    }

    A função ft_sort_three precisa de saber onde está o node com maior value dos três nodes para decidir que rotação fazer.

    > t_stack *stack é o ponteiro para o head da linked list. Cada node (t_stack) tem pelo menos:
      
        - int value -> o número que queremos ordenar.
        - t_stack *next -> o ponteiro para o próximo node (ou NULL, no último node). 

    > int high é a variável onde vamos guardar o maior valor encontrado até ao momento.
      Iniciamos o high em INT_MIN (o menor inteiro possível) para começar pelo valor mais baixo de modo a garantir que o primeiro
      node que virmos seja value > high, atualizando o high e sendo até esse momento o maior valor encontrado.
      Funciona para todos os casos, inclusive quando os números são negativos.

    A linked list é uma cadeia de nodes:

    head → [value = 40, next = &n2] -> [value = -5, next = &n3] -> [value = 12, next = &n4] -> [value = 7, next = NULL] ← tail

    O while (stack) vai:

    - Ler o node atual (aquele para onde o stack aponta agora, no ínicio aponta para o head).
    - Compara o seu value com o high.
    - Se for maior, atualiza high.
    - Avança com stack = stack->next, movendo para o node seguinte.
    - Repete até stack == NULL (fim da lista).

    NOTA: Aqui não alteramos a lista, apenas só lemos o value e seguimos o ponteiro next.

    
    Agora vamos verificar se o maior value está no topo:
    
    if ((*stack_a)->value == high)
        ft_ra(stack_a); 

    A ideia aqui é colocar o maior value na base da stack A com uma rotação. Se ele estiver no topo (se for o head),
    fazemos rotate (ra):

    [c3]

    void	ft_ra(t_stack **stack_a)
    {
	    ft_rotate(stack_a);
	    ft_putstr_fd("ra\n", 1);
    }

    static void	ft_rotate(t_stack **stack)
    {
	    t_stack	*temp;
	    t_stack	*last;

	    if (!*stack || !(*stack)->next)   // se tiver 0 ou 1 node não há nada a fazer
		    return ;
	    temp = *stack;                  // guarda o head antigo (node1)
	    *stack = (*stack)->next;        // avança o head para o node2 (novo topo)
	    last = ft_last(*stack);         // encontra o tail a partir do novo head
	    temp->next = NULL;              // o antigo head (topo) vai ser o novo tail -> next = NULL
	    last->next = temp;              // liga o antigo head (topo) ao fim da lista
    }

    O rotate A (ra) move o topo (head) da stack A para a base.
    A função ft_ra() recebe um t_stack ** porque a rotação altera o head (topo) da lista.
    Se a função recebesse t_stack *stack (cópia do ponteiro), só mudariamos a cópia local e o chamador 
    continuaria a apontar para o head antigo.
    
    > Estado inicial: 
    
    *stack  ──► [N1] ──► [N2] ──► [N3] ──► NULL
                 ^topo              ^base
                 
    O ponteiro *stack aponta para o head (topo) da lista, que neste caso vai ser o N1.

    > temp = *stack // guardamos o head antigo (N1)

    Aqui, copiamos o ponteiro do head para uma variável temporária (temp).
    Agora ficamos com dois ponteiros que fazem referencia ao mesmo node N1: *stack e temp.

      temp ──┐
             ▼
     *stack ──► [N1] ──► [N2] ──► [N3] ──► NULL
                  ^topo

    Nada na lista mudou; apenas guardámos o acesso ao antigo topo para o reaproveitar no fim.

    > *stack = (*stack)->next; // avança o head para N2 (novo topo)

    Mudamos o head (visto pelo chamador) para o segundo node.
    Depois desta linha, o novo topo é o node N2. 
    O temp continua a apontar para N1.

    temp   ─────────────► [N1] ──► [N2] ──► [N3] ──► NULL
    
    *stack ──► [N2] ──► [N3] ──► NULL
                ^topo
    
    A lista ainda está ligada do mesmo jeito; só o ponteiro do head é que mudou.

    
    > last = ft_last(*stack); // encontra o tail a partir do novo head

    Chamamos a função ft_last() a partir do novo head (N2) para descobrir o último node (tail), que é N3.
    A função vai percorrer até encontrar o node cujo next == NULL.
                
    last  ───────────────────────────────────────────────────────────────► [N3] ──► NULL

    temp  ─────────────► [N1] ──► [N2] ──► [N3] ──► NULL

    *stack ──► [N2] ──► [N3] ──► NULL
                ^topo     ^tail (last)

                
    > temp->next = NULL; // o antigo head (N1) vai ser o novo tail → next = NULL

    Estamos a preparar N1 (o antigo topo) para o colocar no fim.
    Definimos que depois dele não há mais nenhum node.

    temp (N1) ─► [N1] ──► NULL          [N2] ──► [N3] ──► NULL
    
    *stack   ──► [N2] ──► [N3] ──► NULL

    last     ───────────────────────────────────────────────► [N3]

    Ainda não ligámos N1 ao resto — só o deixámos “isolado” com next = NULL.

    
    > last->next = temp; // liga o antigo head (N1) ao fim da lista

    *stack ──► [N2] ──► [N3] ──► [N1] ──► NULL
                 ^topo                              ^novo tail

    Agora fazemos a ligação final: o antigo tail (N3) passa a apontar para N1.
    Assim, N1 torna-se o novo tail.

    Fizemos assim a rotação para cima - o topo antigo foi enviado para a base e o 
    segundo node tornou-se o novo topo.

    
    Vamos verificar o caso de o maior estar no meio da lista:

    else if ((*stack_a)->next->value == high)  // verifica se o maior está no meio
		 ft_rra(stack_a); [c4]             // se sim, desloca o que está na base para o topo -> o maior desliza para a base

    Se o maior estiver no meio, uma rotação para baixo (rra) traz o último node (base) para o topo.
    QUando isso acontece com 3 elementos, o node do meio desce uma posição e vai parar à base - que é onde queremos o maior.

    A função ft_rra() move a base (o último node) para o topo.

    [c4]

    void	ft_rra(t_stack **stack_a)
    {
	    ft_reverse_rotate(stack_a);
	    ft_putstr_fd("rra\n", 1);
    }

    static void	ft_reverse_rotate(t_stack **stack)
    {
	    t_stack	*temp;
	    t_stack	*last;
	    t_stack	*before_last;

	    if (!*stack || !(*stack)->next)
		    return ;
            
	    last = ft_last(*stack);
	    before_last = ft_before_last(*stack);
	    temp = *stack;                          // guarda o head antigo
        
	    *stack = last;             // o novo head passa a ser o tail
	    (*stack)->next = temp;     // o antigo head fica a seguir ao novo head
	    before_last->next = NULL;  // corta a lista no antes do ultimo node - ele torna-se o nove tail
    }

    > Estado Inicial: 

    *stack ──► [N1] ──► [N2] ──► [N3] ──► NULL
                ^topo              ^base (tail)

    O node N2 é o node que contém o maior valor (value).

    
    > last = ft_last(*stack);

    Procura o último node (tail), partindo do head:

    last ───────────────────────────────► [N3] ──► NULL
    
    *stack ──► [N1] ──► [N2] ──► [N3] ──► NULL

    
    > before_last = ft_before_last(*stack);

    t_stack	*ft_before_last(t_stack *stack)
    {
	    while (stack && stack->next && stack->next->next)
		    stack = stack->next;
	    return (stack);
    }

    Procura o node antes do último (antes do tail):

    before_last ───────────────────────► [N2] ──► [N3] ──► NULL
    
    last         ──────────────────────────────► [N3]

    *stack       ──► [N1] ──► [N2] ──► [N3] ──► NULL
    
    
    > temp = *stack; // guarda o head antigo (topo)

    temp   ──► [N1] ──► [N2] ──► [N3] ──► NULL
    
    *stack ──► [N1] ──► [N2] ──► [N3] ──► NULL

    before_last ─────► [N2]

    last        ─────► [N3]

    
    > *stack = last; // o novo head passa a ser o tail

    Agora o novo topo é o antigo tail (N3):

    stack ──► [N3]      (novo topo)
    
    temp   ──► [N1] ──► [N2] ──► [N3] ──► NULL

    before_last ─────► [N2]

    last        ─────► [N3]


    > (*stack)->next = temp; // liga o novo topo ao antigo head

    Faz N3->next = N1, ligando o antigo head a seguir ao novo head:

    *stack ──► [N3] ──► [N1] ──► [N2] ──► [N3] ──► ...  ❌ (há um ciclo!)
                 ^topo

    temp   ──► [N1] ──► [N2] ──► [N3] …

    before_last ─────► [N2]

    last        ─────► [N3]

    Neste momento, se não cortarmos o tail antigo, criamos um ciclo (porque N2->next ainda aponta para N3,
    e N3->next aponta agora para N1). O próximo passo resolve isso.


    > before_last->next = NULL; // corta no “antes do último”

    Define que o novo tail é o before_last (N2), cortando a ligação antiga N2->next = NULL:

    *stack ──► [N3] ──► [N1] ──► [N2] ──► NULL
                ^topo              ^novo tail


    Depois de garantirmos que o node com o maior value está na base (com ra, caso estivesse no topo ou com rra no caso 
    estivesse no meio), só falta agora ordenar os dois de cima (o topo e o meio) de modo a que fiquem em ordem crescente:

    if ((*stack_a)->value > (*stack_a)->next->value)  // topo > meio ?
        ft_sa(stack_a);

    Por que só precisamos ver estes dois nodes?

    Na função ft_sort_three(), já tratamos de pôr o maior na base (com ra ou rra).
    Logo, a base está correta (o maior deve ficar na base).

    Só resta “arrumar” os dois de cima.
    Se topo > meio, trocamos; se topo < meio, não fazemos nada.

    Isto garante o sort com no máximo 2 instruções (ra/rra + sa opcional).

    > *stack_a → é o topo (head) da lista.

    > (*stack_a)->next → é o meio (o segundo node).

    > (*stack_a)->value > (*stack_a)->next->value   →   “O valor do topo é maior do que o valor do meio?”

       - Se sim, então os dois não estão ordenados (devia ser topo < meio numa lista crescente).
       - Se não, já estão na ordem certa.

    No push_swap não há duplicados, logo a ordem “certa” é estritamente crescente: topo < meio.

    A funçaõ ft_sa() troca os dois primeiros nodes da stack A (troca os conteúdos value e o index do topo e do meio).
    Isto corrige imediatamente a ordem desses dois:

    Antes (errado): [ topo=5, meio=2, base=MAIOR ] →  sa  → Depois (certo): [ topo=2, meio=5, base=MAIOR ]

    Como o node com o value maior já foi colocado na base no passo anterior, depois deste sa (se necessário) a pilha fica: [menor, médio, maior]
    

    Voltando À função ft_push_swap(), vamos debater-nos sobre o caso de haver mais do que 3 nodes na lista e estes não estarem ordenados:

    > else if (size > 3 && !ft_is_sorted(*stack_a))
		ft_sort(stack_a, stack_b);
        
    Se temos mais do que 3 números e estão desordenados -> entra no algoritmo completo ("turkish + reinserção pelo movimento com menos custo").


    > ft_sort(stack_a, stack_b)
    
    void	ft_sort(t_stack **stack_a, t_stack **stack_b)
    {
	    ft_push_to_b(stack_a, stack_b);  // aqui dividimos: tiramos quase todos da stack A para a stack B
	    ft_sort_three(stack_a);  // ordenamos rapidamente os 3 que ficaram na stack A
	    while (*stack_b)         // enquanto houver na stack B, reinserimos da stack B para a stack A, sempre no sítio certo e pelo menor custo
	    {
		    ft_assign_pos(stack_a, stack_b);  // calculamos a posição de A e B e o target de cada node de B
		    ft_cost(stack_a, stack_b);    // calculamos os custos (ra/rra, rb/rrb) com sinal
		    ft_cheapest(stack_a, stack_b);  // escolhemos e executamos o movimento total mais barato e fazemos pa
	    }
	    if (!ft_is_sorted(*stack_a) && *stack_a)  // ajuste final
		    ft_stack_shift(stack_a);  // roda A até o menor indice (0) ficar no topo
    }

    É nesta função, do push swap, que transformamos uma stack A com mais do que 3 números numa stack A ordenada (topo -> base).

    O objetivo da função ft_sort() é levar a stack_a do estado desordenada e demasiado grande para o estado de ordenada e com o 
    node menor no topo, deixando a stack B vazia.
    Temos, assim, de deixar a stack A ordenada (topo -> base) e a stack B vazia, imprimindo a menor quantidade razoável de instruções.

    No fim do processo, a stack B fica vazia. A stack A fica toda ordenada e com o menor no topo.

    

    > ft_push_to_b(a, b)

    static void	ft_push_to_b(t_stack **stack_a, t_stack **stack_b)
    {
	    int	size;
	    int	i;
	    int	is_pushed;

	    size = ft_size(*stack_a);                    // tamanho inicial da stack A
	    is_pushed = 0;                               // quantos pb já fizemos (quantos sairam da stack A)
	    i = 0;                                       // quantas visitas (iterações) ao topo já fizemos
        
	    while (size > 6 && i < size && is_pushed < size / 2) 
	    {
		    if ((*stack_a)->index <= size / 2)        // verificamos se o topo tem um indice baixo
		    {
			    ft_pb(stack_a, stack_b);  [d2]        // se tiver, empurramos para a stack B
			    is_pushed++;
		    }
		    else
			    ft_ra(stack_a);  [d2]                 // se não tiver, rodamos A (ra) para experimentarmos outro topo, à procura de alguém com indice mais baixo
		    i++;
	    }
	    while (size - is_pushed > 3)                  // enquanto a stack A tiver mais que 3
	    {
	    	ft_pb(stack_a, stack_b);  [d2]            // empurramos para a stack B
	    	is_pushed++;
	    }
    }

    Utilizamos esta função pois ordenar uma lista grande só com rotações/trocas sai caro.

    O objetivo é deixarmos apenas 3 elementos na stack A (fáceis de ordenar). Como fazemos isso? Empurramos da stack A para a stack B 
    quase todos os elementos, privilegiando que os de índice mais baixo saiam primeiro.
    No fim, a stack A fica com 3 nodes e a stack B fica com o resto.

    O que isto garante? Reduz drasticamente a complexidade: a stack A vira uma espécie de “núcleo” pequeno e a stack B guarda o volume.

    Assim: - Movemos de A para B aproximadamente metade dos elementos com índices baixos (0..N/2) e, depois, empurramos mais até 
             sobrarem 3 nodes em A.
           - Usa o index (0..N-1) para decidir quem empurrar: comparar índices é simples e independente do sinal/magnitude dos 
             valores reais.

    Sem esta fase: ficariamos a tentar ordenar tudo dentro de A, com muito mais ra/rra/sa — gastariamos muitas operações.
    
    
    > o que é “índice baixo” ? Depois da função ft_index_stack(), cada node ficou com um index ∈ [0..N-1]:

      - 0 = menor valor e N-1 = maior valor.
      
      - O “índice baixo” = indice perto de 0.
    
      A função usa isto para empurrar primeiro os “pequenos” para B.

    > size: é o número de nodes que a stack_a contém. Serve para termos um limiar fixo (size / 2) para decidir os indices baixos e 
            para controlar quantas iterações vamos fazemos no primeiro loop (na condição i < size).

    > is_pushed: é o número de quantos nodes empurramos de A para B (quantos pb fizemos), ou seja, quantos nodes saíram da stack A.
                 Em qualquer momento, size - is_pushed, significa "quantos nodes ainda estão na stack A".

    
    Vejamos como isto funciona:

    Fase 1 - Fase dos chunks (se size > 6): 

    > while (size > 6 && i < size && is_pushed < size / 2)
      
    Se o topo tem índice baixo (<= size / 2) -> empurramos da stack A para a stack B (pb).
    Caso contrário, rodamos a stack A, trazendo outro node ao topo para testarmos.
    EM qualquer caso, i++, contamos com uma visita ao topo.

    O loop para quando visitamos todos os size topos ou quando já empurramos size / 2 nodes da stack A para a stack B.

    Numa única ronda sobre os size topos, tentamos tirar aproximadamente metade (aqueles com index <= size /2 - os 
    de indice mais baixo) da stack A e empurramos para a stack B, deixando a stack B carregada de indices baixos e a 
    stack A com uma boa parte dos indices altos.

    Fase 2 - Garantir 3 nodes restantes na stack A
    
    > while (size - is_pushed > 3)  // enquanto a stack A tiver mais do que 3 nodes, fazemos pb
    
    Independentemente do que aconteceu acima, empurramos para B até ficarmos só com 3 na stack A.
    
        - Para size = 4, vamos empurrar 1; size = 5 empurramos 2; size = 6 empurramos 3; etc.

    Caso size <= 6, saltamos a primeira fase (o primeiro while) e vamos diretos para este loop. 
    SImplesmente, empurramos até sobrarem 3 elementos na stack A (sem seleção por indice).

        O critério do “3 restantes” é porque temos a função ft_sort_three() para lidar com os 3 elementos.


    > O que pb faz: 
    
      - pb — “push B”: move o topo (head) de A para o topo (head) de B

        Antes: A (topo→) [A1] → [A2] → [A3] → ...
               B (topo→) [B1] → [B2] → ...

        Com pb: - Na stack A a head passa a ser A2.
                - Na stack B, a nova head passa a ser A1.

        Depois: A: [A2] → [A3] → ...
                B: [A1] → [B1] → [B2] → ...
        
                
        void	ft_pb(t_stack **stack_a, t_stack **stack_b)
        {
	        ft_push(stack_a, stack_b);
	        ft_putstr_fd("pb\n", 1);
        }

        void	ft_push(t_stack **src, t_stack **dest)
        {
	        t_stack	*temp_src;
	        t_stack	*temp_dest;

	        if (!*src)
		        return ;
	        temp_src = *src;
	        temp_dest = *dest;
	        *src = temp_src->next;
	        *dest = temp_src;
	        temp_src->next = temp_dest;
        }

        > Estado inicial:

        src é a nossa stack A e dest é a nossa stack B.
        Assim:

        stack_a (*src)  ──► [ A1 ] ──► [ A2 ] ──► [ A3 ] ──► NULL
                               ^ topo A 
        
        stack_b (*dest) ──► [ B1 ] ──► [ B2 ] ──► ...      ──► NULL
                               ^ topo B

                               
        > temp_src = *src;  (temp_stack_a = *stack_a)

        Guarda o endereço do head/topo da src (stack_a) (o node que vamos deslocar).
        
        temp_stack_a ─► [ A1 ] ──► [ A2 ] ──► ...
        
        *stack_a     ─► [ A1 ] ──► [ A2 ] ──► ...

        *stack_b    ─► [ B1 ] ──► [ B2 ] ──► ...

        
        > temp_dest = *dest;  (temp_stack_b = *stack_b)

        Guarda o endereço do head/topo da dest (stack_b) (para encaixar depois o movido “em cima” dele).

        temp_stack_b ─► [ B1 ] ──► [ B2 ] ──► ...
        
        temp_stack_a  ─► [ A1 ] ──► [ A2 ] ──► ...
        
        *stack_a      ─► [ A1 ] ...
        
        *stack_b     ─► [ B1 ] ...
        

        > *src = temp_src->next;  (*stack_a = temp_stack_a->next)

        Avançamos o head da stack_a (src): agora o novo head/topo da stack_a é A2.

        *stack_a      ──► [ A2 ] ──► [ A3 ] ──► ...
    
        temp_stack_a  ──► [ A1 ] ──► [ A2 ] ──► ...

        *stack_b     ──► [ B1 ] ──► [ B2 ] ──► ...

        temp_stack_b ──► [ B1 ] ──► [ B2 ] ──► ...

        
        > *dest = temp_src;  (*stack_b = temp_stack_a)

        O head da stack_b passa a ser o node movido A1.

        *stack_b      ──► [ A1 ] ──► [ A2 ] ──► ...   (ainda não correcto; falta apontar o next de A1 para o head antigo de B)

        temp_stack_a  ──► [ A1 ] ──► [ A2 ] ──► ...

        temp_stack_b  ──► [ B1 ] ──► [ B2 ] ──► ...

        *stack_a      ──► [ A2 ] ──► [ A3 ] ──► ...


        > temp_src->next = temp_dest;  (temp_stack_a->next = temp_stack_b)

        Liga o node movido (A1) por cima do que era o head da stack B (dest), B1.

        *stack_b     ──► [ A1 ] ──► [ B1 ] ──► [ B2 ] ──► ...

        *stack_a      ──► [ A2 ] ──► [ A3 ] ──► ...


        Recapitulando: 
        
        Antes: src (*src)  ──► [ A1 ] ──► [ A2 ] ──► [ A3 ] ──► NULL
                                  ^ topo A

               dest(*dest) ──► [ B1 ] ──► [ B2 ] ──► ...      ──► NULL
                                  ^ topo B

        Depois: src (*src)  ──► [ A2 ] ──► [ A3 ] ──► NULL
                                   ^ novo topo A

                dest(*dest) ──► [ A1 ] ──► [ B1 ] ──► [ B2 ] ──► ...
                                   ^ novo topo B

    Por que usamos o índice (e não o value)?

    Decidir pelo index (0..N-1) é super simples para “dividir pela metade” (index <= size/2) e não depende de sinais/magnitudes.
    Pequeno exemplo (N=8, índices no topo→base)

    Suponhamos A começa: A: [7, 0, 5, 3, 6, 1, 4, 2] 
                         B: [], 
                         size = 8

    Fase 1 (size > 6 e queremos empurrar ~4 (size / 2 = 8 / 2) vezes):

        - Para i = 0, o topo = 7 (como 7 > 4, é alto) → ra
        - Para i = 1, o topo = 0 (como 0 < 4, é baixo) → pb (B:[0])
        - Para i = 2, o topo = 5 (como 5 > 4, é alto) → ra
        - Para i = 3, o topo = 3 (como 3 < 4, é baixo) → pb (B:[3,0])
        - Para i = 4, o topo = 6 (como 6 > 4, é alto) → ra
        - Para i = 5, o topo = 1 (como 1 < 4, é baixo) → pb (B:[1,3,0])
        - Para i = 6, o topo = 4 (como 4 == 4, é baixo) → pb (B:[4,1,3,0]) → já empurrámos 4 = size / 2 → Fase 1 termina

    A: [2,7,5,6]
    B: [4,1,3,0]     (maioria índices baixos em B)

    Fase 2: ficar só com 3 na stack A → size - is_pushed = 8 - 4 = 4 → empurramos mais um para ficar com 3.

    A: [7,5,6]
    B: [2,4,1,3,0]

    
    > ft_sort_three(a)

    Com 3 elementos na stack A, conseguimos ordenar em <= 2 instruções.

    A função ft_sort_three() ordena a stack A (do topo para a base), em ordem crescente, com o minimo de operações.

    Imaginemos a stack A:

    Topo (head)  →  [a]  →  [b]  →  [c]  →  NULL  =  Base (fundo)
                     ^topo   ^meio   ^base

    As operações usadas: - sa → troca os dois do topo ([a] com [b]).
                         - ra → roda para cima: o topo vai para a base  ->  [a, b, c] → ra → [b, c, a]
                         - rra → roda para baixo: a base vem para o topo.  ->  [a, b, c] → rra → [c, a, b]

    A ideia é pôr o maior na base com 1 rotação (ra ou rra) e depois, se os dois de cima estiverem desordenados, fazer 1 swap (sa).
    Com isso ficamos com a stack A ordenada, do topo para a base [menor, médio, maior].
                                                                   ^topo  ^meio  ^base

    Como isto funciona sempre ? Com 3 elementos, há só 6 ordens possíveis em que em todas elas:

        > com um rotate ou reverse rotate (ra ou rra) conseguimos colocar o maior na base.
        
              [a, b, c] → ra → [b, c, a]   ou   [a, b, c] → rra → [c, a, b]

        > se os dois de cima (o topo e o meio) estiverem desordenados (topo > meio), trocamos eles com o swap (sa).
        
    Utilizamos assim no máximo duas operações.

    A função ft_sort_three() precisa de saber onde está o maior dos três para decidir que rotação fazer:

        - se o maior está no topo → ra (o topo vai para a base)  ->  [a, b, c] → ra → [b, c, a]
        - se o maior está no meio → rra (a base vai para o topo, empurrando o meio para a base)  ->  [a, b, c] → rra → [c, a, b]
        - se não está no topo nem no meio, então está na base → não roda.
    
        - Encontramos o maior e colocamos ele na base com ra (se estava no topo) ou com rra (se estava no meio).
        - Se for necessário, se os dois do topo (topo e meio) estiverem desordenados, utilizamos sa.
    
    Garante que, no fim, a stack A fica com uma base ordenada - [menor, médio, maior] - pronta para receber os restantes
    elementos que estão na stack B.

    Sem esta fase, ao reintroduzirmos os valores na stack A exigiria reposicionar também o “núcleo”, complicando os custos e
    aumentando os movimentos.


    > Reinserção
    
      while (*stack_b)         // enquanto houver na stack B, reintroduzimos no local certo
	  {
		ft_assign_pos(stack_a, stack_b);  // (re)calculamos a posição de A e B e o target para cada node de B
		ft_cost(stack_a, stack_b);    // para cada node de B, calculamos os custos cost_a / cost_b (ra/rra, rb/rrb) com sinal
		ft_cheapest(stack_a, stack_b);  // escolhemos o node com menor custo total, rodamos (rr/rrr quando dá) e faz pa
	  }
       

    Depois de deixarmos apenas 3 elementos na stack A (e ordenarmos esses 3), ficamos com muitos elementos na stack B. 
    Agora, voltamos a inserir os elementos da stack B para a stack A um a um, sempre:

        - calculando as posições atuais nas stacks A e B (pos);
        - descobrindo, para cada node da stack B, onde deve entrar na stack A para manter A ordenada (target);
        - calculando quantas rotações precisamos na stack A e na B para alinhar (cost_a, cost_b);
        - escolhendo o node com menos custo da stack B e executando as rotações adequadas (aproveitando rr/rrr), depois pa.

    Este loop repete-se até a stack B ficar vazia.

    Porque recalcular sempre? Porque a cada iteração rodamos a stack A/B e fazemos um pa. Isso muda quem é o topo e, portanto, 
    todas as posições. Se pos muda, também podem mudar o target e os custos.
    Assim, a cada iteração, as posições mudam, pois rodamos/empurramos, por isso, temos de recalcular pos e target sempre.

    Vejamos como calcular a posição:
    
    void	ft_positon(t_stack **stack)
    {
	    t_stack	*tmp;
	    int		i;    // contador de posição

	    i = 0;        // começamos no topo
	    tmp = *stack;  // tmp aponta para o head/topo da lista (o topo da stack)
	    while (tmp)    // vamos percorrer a lista, node a node, até tmp == NULL
	    {
		    tmp->pos = i;
		    tmp = tmp->next;
		    i++;
	    }
    }

    Esta função serve para atribuir a cada node da stack a sua posição atual a partir do topo. 
    Ela percorre a lista do topo até à base e atribui pos = 0, 1, 2, ..., para o head/topo, 2º node, 3º node, ..., 
    respetivamente.
    Fazemos isso separadamente para a stack A e para a stack B.
    Isto é fundamental para os custos, pois a variável pos é essencial para decidir como rodar:

        - Se um node está perto do topo (posições pequenas), costuma ser mais barato usar a rotação normal (ra/rb).
        - Se está mais perto da base, é mais barato usar a rotação inversa (rra/rrb).
    
    Ou seja, isto é crucial na fase da reinserção: saber a posição pos permite calcular quantas rotações são precisas (e se é
    melhor a rotação normal ra/rb ou a inversa rra/rrb).
    A pos diz quantas rotações normais (ra/rb) precisamos e por comparação com o meio da stack, sabemos quando é melhor fazer a 
    rotação inversa (rra/rrb).

    
    > O que é a variável pos? A variável pos é a posição atual do node na stack, a contar a partir do topo/head:

    Topo/head → pos = 0
     2.º node → pos = 1
     3.º node → pos = 2

    … e assim até à base.

    A posição é relativa ao estado atual da stack. Se rodarmos a stack (ra, rra, rb, rrb), as posições mudam.

        
    > Como a função ft_position() define as posições (pos) ?

    Calcula pos (0 = topo, 1, 2, …) para todos os nodes da stack A e da stack B.

        > tmp = *stack 

        tmp aponta para o head da lista (o topo da stack).

        Esquema inicial: *stack (topo) ──► [N1] ──► [N2] ──► [N3] ──► ... ──► [Nk] ──► NULL
                                             ^tmp

        > while (tmp) - Vamos andar pela lista, nó a nó, até tmp == NULL (fim).

        Primeira iteração: - tmp está no N1 (topo).
                           - tmp->pos = i; → N1.pos = 0
                           - tmp = tmp->next; → avança para N2
                           - i++ → i = 1

        Segunda iteração:  - tmp está no N2 (2º node).
                           - tmp->pos = i; → N2.pos = 1
                           - tmp = tmp->next; → avança para N3
                           - i++ → i = 2

        Terceira iteração: - tmp está no N3 (3º node).
                           - tmp->pos = i; → N3.pos = 2
                           - tmp = tmp->next; → avança para N4
                           - i++ → i = 3

                    … e assim sucessivamente, até ao final.

        Última iteração (no Nk): - tmp está no Nk (base/head).
                                 - tmp->pos = i; → Nk.pos = k-1
                                 - tmp = tmp->next; → NULL
                                 - tmp == NULL, sai do while.

        Topo → Base
        [N1 pos=0] → [N2 pos=1] → [N3 pos=2] → [N4 pos=3] → NULL

        
    Porque isto é indispensável no push swap? 
    
        Durante a reinserção (trazer elementos da stack B para a stack A), para cada node da stack B queremos saber: 
        
            - Quantas rotações na stack B para colocá-lo no topo?
              
              Para trazer um node ao topo, sabemos exatamente quantas rotações normais precisamos - ou seja, pos.
              Para decidir rotação normal vs rotação inversa, comparamos a posição com o meio da stack.

              → Se pos_b for pequeno, é barato fazer "rb" "pos_b" vezes;
              → se pos_b for grande (mais perto do fim), é mais barato fazer "rrb" "(size_b - pos_b)" vezes.
                Ou seja, se pos > size / 2, normalmente é mais barato fazer rotações inversas: size - pos.

                Ex.: topo já é 0 → 0 rotações; se for 3 → 3 rotações normais.

            - Quantas rotações na stack A para alinhar com o target (posição onde o node de B deve entrar)?
                
                → Mesmo raciocínio com o target e com o size_a.

                Na função ft_cost(), a posição pos:

                    > Para B: - Se pos_b <= size_b / 2 → cost_b = + pos_b (usamos rb).
                              - Se pos_b > size_b / 2 → cost_b = - (size_b - pos_b) (usamos rrb).

                    > Para A (usando o target calculado para aquele node de B): - Se target <= size_a / 2 → cost_a = + target (usamos ra).
                                                                                - Se target > size_a / 2 → cost_a = - (size_a - target) (usamos rra).

                O sinal (+ / −) permite, depois, combinar rotações: - mesmo sinal → dá para usar rr (ambos +) ou rrr (ambos −) para rodar as duas pilhas
                                                                      ao mesmo tempo, reduzindo o número de instruções.
        
  
    > Como a posição pos muda com as rotações ?

        - Exemplo com ra (rodar A para cima, ou seja, ra move o head/topo para a base):

        Antes:   A:  [v=40 | i=7 | p=0] → [v=10 | i=1 | p=1] → [v=30| i=5 | p=2] → [v=50| i=9 | p=3] → NULL

        Com ra:  A:  [v=10 | i=1 | p=?] → [v=30| i=5 | p=?] → [v=50| i=9 | p=?] → [v=40 | i=7 | p=?] → NULL

        Recalculamos a pos: 
        
                A:  [v=10 | i=1 | p=0] → [v=30| i=5 | p=1] → [v=50| i=9 | p=2] → [v=40 | i=7 | p=3] → NULL

             
        - Exemplo com rra (rodar para baixo, ou seja, rra traz a base para o topo): 

        Antes:   A:  [v=40 | i=7 | p=0] → [v=10 | i=1 | p=1] → [v=30| i=5 | p=2] → [v=50| i=9 | p=3] → NULL

        Com rra: A:  [v=50| i=9 | p=?] → [v=40 | i=7 | p=?] → [v=10 | i=1 | p=?] → [v=30| i=5 | p=?] → NULL

        Recalculamos a pos:

             A:  [v=50| i=9 | p=0] → [v=40 | i=7 | p=1] → [v=10 | i=1 | p=2] → [v=30| i=5 | p=3] → NULL



    Vejamos como calculamos o target (posição na stack A onde esse node deve entrar para manter A ordenada):

    > ft_target(stack_a, tmp->index, INT_MAX, target)

    int	ft_target(t_stack **stack_a, int b_index, int target_index,
				int target_pos)
    {
	    t_stack	*tmp;

	    tmp = *stack_a;  // começamos no topo da stack A
        
        // 1) Tentar encontrar o sucessor (o menor indice da stack A que seja > b_index)
        
	    while (tmp)  // vamos percorrer a stack A ...
	    {
		    if (tmp->index > b_index           // verificamos se o indice do node de A é maior do que o indice do B (filtramos apenas quem é maior que b_index)
                && tmp->index < target_index)  // e se é menor do que o melhor candidato já visto ?  (entre os maiores, guarda o menor - o sucessor)
		    {
			    target_index = tmp->index;      // atualiza o melhor indice (novo sucessor) -> sempre que encontramos um candidato, atualizamos
			    target_pos = tmp->pos;          // e guarda a posição desse node na stack A
		    }
		    tmp = tmp->next;                     // avança para o próximo node
	    }
        
	    if (target_index != INT_MAX)             // verificamos se encontrou algum sucessor
		    return (target_pos);                 // se sim, devolve a posição dele
            
	    tmp = *stack_a;     // recomeçamos no topo da stack A
        
        // se não há sucessor (b_index é maior do que todos) inserimos antes do menor indice na stack A
	    while (tmp)             // percorremos a stack A toda outra vez 
	    {
		    if (tmp->index < target_index)   // verificamos se é o menor indice (menor indice visto)
		    {
			    target_index = tmp->index;   // se for, atualizamos (novo menor)
			    target_pos = tmp->pos;       // guarda a posição do menor
		    }
		    tmp = tmp->next;                 // avançamos
	    }
	    return (target_pos);                 // devolve a posição do menor
    }

    O que é target? 
    
    É a posição na stack A onde o node da stack B deve ser inserido para manter A ordenada, por índice (que corresponde a ordenar por valor real).

    Dado um node da stack B (com indice b_index), a função ft_target() diz em que posição da stack A (target_pos) devemos alinhar o topo
    antes de fazermos pa, para que esse node entre no lugar certo e a stack A continue ordenada por índices (ordem circular).

    A ordem circular é quando a stack A está em ordem crescente por index, mas o menor (index = 0) pode ainda não estar no topo (o que 
    será corrigido no fim com a função ft_stack_shift).

    A função ft_target() utiliza a posiçaõ pos dos nodes da stack A para devolver um número da posição (target_pos).
    Depois, a função ft_cost() utiliza esse target_pos para calcular quantas rotações a stack A precisa (ra/rra) para colocar esse node no topo,
    antes de fazer pa.

    > b_index: corresponde ao indice do node que está na stack B e que queremos colocar agora na stack A.

    > Lógica do “successor”: 

        - Queremos o primeiro elemento maior do que b_index, mas entre os maiores, queremos o mais pequeno (o “successor”).
        - Ou seja, dentro dos indices existentes na stack A que são maiores que b_index, queremos o mais pequeno desses.
          Em termos de ordem, o sucessor é o próximo a seguir ao b_index.
        - A posição (pos) do successor será o target_pos: alinhar a stack A nessa posição e fazer pa insere antes dele.

    > candidato: enquanto percorremos a stack A, o candidato corresponde ao melhor sucessor encontrado até agora.
    > target_index: corresponde ao indice do candidato atual. Começa com INT_MAX ("ainda não tenho nenhum").
    > target_pos: é a posição (na stack A) onde o node da stack B deve cair (ou seja, a posição do sucessor, ou do menor, no segundo while). 
                  É o número que a ft_target devolve; ft_cost() usa-o para escolher ra vs rra e quantas rotações fazer na stack A para alinhar 
                  esta posição no topo antes de fazer pa.

    > A ideia aqui é: “onde, na stack A, coloco o node da stack B para manter a ordem?” → “coloco-o antes do seu successor (primeiro while)! 
      Se não tem successor (é o maior de todos), coloco-o antes do menor (segundo while)”.

    > Para um node que está na stack B com índice b_index, queremos saber em que posição de A (target_pos) ele deve entrar para manter a stack A ordenada
      por índice:

            - Se existir na stack A alguém com índice maior do que b_index, escolhe o menor desses (o successor) e devolve a posição dele.
            - Se não existir (ou seja, b_index é maior do que todos os índices atualmente na stack A), devolve a posição do menor índice de A 
              (ordem circular → “entra antes do menor”).

    A ft_target usa esse pos para devolver um número (não um ponteiro), que ft_cost converte em ra/rra.

    Como as fases se relacionam?

    Fase 1 tenta achar o successor.
    Se achar, sai imediatamente com return target_pos.
    Não entra na fase 2.

    Só entra na fase 2 quando a fase 1 não encontrou o successor (ou seja, ninguém na stack A tem index > b_index).
    Aí escolhe a posição do menor de A.


    1º while - encontrar o sucessor
    
    Tem como objetivo de, entres todos os nodes da stack A, filtrar os que têm index > b_index e, entre esses, escolher o que tem menor index.
    Porquê? Porque ao inserirmos antes do sucessor mantém a ordem.
    
    > tmp = *stack_a 

    COmeçamos no topo/head da stack A:

    *stack_a ──► [A0] → [A1] → [A2] → ... → [Ak] → NULL
                   ^
                   tmp

    - b_index vem do node da stack B que vamos inserir agora.
    - target_index começa com INT_MAX: ainda não temos candidato.
    - target_pos começa com, p.ex: 0, vai ser atualizado quando encontrarmos um candidato.

    > while (tmp)

    Percorremos todos os nodes da stack A.

        > if (tmp->index > b_index && tmp->index < target_index) — condição do “successor”

        Procuramos o primeiro índice maior do que b_index, mas o mais pequeno possível entre os maiores.

            - tmp->index > b_index → o candidato precisa de ser maior do que b_index (senão não o podemos inserir antes dele).
            - tmp->index < target_index → e tem de ser o menor entre os maiores.
            
        > Atualiza o melhor candidato
           
          target_index = tmp->index;
		  target_pos = tmp->pos; 

        Se a condição passou, guardamos:

            - target_index = tmp->index (o melhor índice encontrado até agora),
            - target_pos = tmp->pos (a posição desse node na stack A).

        Aqui entra ft_position(): tmp->pos é o valor que ft_position escreveu. Sem ele, não saberiamos em que posição alinhar na 
        stack A.        

    > if (target_index != INT_MAX) return (target_pos);

      Se encontrámos pelo menos um “maior que b_index”, devolvemos a posição do menor entre eles (o “successor”).
      Isto cobre o caso normal (quando b_index não é o maior de todos), ou seja, cobre o caso de existir alguém na stack A com indice 
      maior do que b_index.
      Ele devolve a posição desse próximo maior (é aó que queremos alinhar a stack A).


      Exemplo — CASO NORMAL (há successor)

      Vamos exibir [índice | pos] (o pos veio de ft_position(&A) imediatamente antes):

      A (topo→base): [i=3 | p=0] → [i=8 | p=1] → [i=12 | p=2] → [i=20 | p=3] → NULL

      B (node a inserir na stack A): b_index = 9

      Passagem 1 (procurar successor)

      Frame 1
      tmp = A0 → tmp->index = 3
      Condição: 3 > 9? não → ignora
      tmp = tmp->next → A1

      Frame 2
      tmp = A1 → tmp->index = 8
      8 > 9? não → ignora
      tmp = A2

      Frame 3
      tmp = A2 → tmp->index = 12
      12 > 9? sim e 12 < target_index (INT_MAX)? sim → match
      Atualiza: target_index = 12, target_pos = 2
      tmp = A3

      Frame 4
      tmp = A3 → tmp->index = 20
      20 > 9? sim mas 20 < 12? não → mantém (12, pos=2)
      tmp = NULL → acabou a 1ª passagem.

      Como target_index != INT_MAX → retorna target_pos = 2.
      Interpretação (o que fazer com 2?)

      Queres pôr o node de B (9) antes do 12.

      Para isso, a stack A deve ser rodada até que a pos 2 (onde está o 12) fique no topo:

        - se size_a = 4, pos 2 está exatamente no meio → pode ser ra ra ou rra rra conforme estratégia/custos combinados com B; ft_cost decide.

      Em paralelo, a stack B deve pôr esse node (b_index = 9) no topo (via rb/rrb).
      Depois pa → 9 entra antes do 12.
      Nova A (circularmente ordenada): [ 3, 8, 9, 12, 20 ].

        Ou seja: - O que isto quer dizer? Devemos alinhar a stack A para que a posição 2 (onde está o indice 12) vá para o topo.
                 - Em paralelo, devemos alinhar a stack B para colocar o node b_index = 9 no topo.
                 - Depois fazemos pa: o de indice 9 entra antes do de indice 12.
                 - Nova A (circularmente ordenada): [3, 8, 9, 12, 20] (o menor pode não estar no topo; no fim usamos ft_stack_shift).

    
    2º while - ocorre quando não encontramos o sucessor e que b_index é maior que todos os indices atualmente na stack A.
    
    O objetivo é inserir b_index antes do menor indice da stack A -> mantém a ordem circular.
        
    >  while (tmp)             // percorremos a stack A toda outra vez 
	
    Se não existia nenhum índice maior (ou seja, b_index é maior que todos na stack A).
    Para manter a ordem circular, a inserção correta é antes do menor índice da stack A (por isso devolvemos a posição do menor).
    

    EXEMPLO - NÃO HÁ SUCESSOR

    Vamos exibir [índice | pos] (o pos veio de ft_position(&A) imediatamente antes):

      A (topo→base): [i=3 | p=0] → [i=8 | p=1] → [i=12 | p=2] → [i=20 | p=3] → NULL

      B (node a inserir na stack A): b_index = 9

    Passagem 1 (successor) — não encontra ninguém

    A0: 3 > 27? não

    A1: 8 > 27? não

    A2: 12 > 27? não

    A3: 20 > 27? não → nenhum match.

    Passagem 2 (menor de A)

    Frame 1
    tmp = A0 → 3 < INT_MAX? sim → target_index = 3, target_pos = 0
    tmp = A1

    Frame 2
    8 < 3? não → mantém (3, pos=0)
    tmp = A2

    Frame 3
    12 < 3? não
    tmp = A3

    Frame 4
    20 < 3? não
    tmp = NULL → fim

    Retorna target_pos = 0.
    
    Interpretação

    Insere antes do menor (idx=3, pos 0):
    Alinha a stack A para pos 0 (já está no topo neste exemplo), alinha B, pa → a stack A fica [ 27, 3, 8, 12, 20 ] (ordem circular mantida).

    No fim do algoritmo, ft_stack_shift põe o 0 (menor índice) no topo, ficando [3, 8, 12, 20, 27].

    
    Agora vamos ver como entra o target na função ft_assign_pos():
 
     > ft_assign_pos(a, b)

    void	ft_assign_pos(t_stack **stack_a, t_stack **stack_b)
    {
	    t_stack	*tmp;
	    int		target;

	    tmp = *stack_b;
	    target = 0;
        
	    ft_positon(stack_a);  // atualiza pos em A
	    ft_positon(stack_b);  // atualiza pos em B
	    while (tmp)
	    {
		    target = ft_target(stack_a, tmp->index, INT_MAX, target);
		    tmp->target = target;
		    tmp = tmp->next;
	    }
    }

    Para cada node da stack B, descobrimos em que posição da stack A esse node deve ser colocado, de forma a que a stack A
    continue ordenada (o que representa o target).
    O target é, assim, a posição na stack A onde esse node deve entrar para manter A ordenada.

        - procura na stack A o primeiro índice maior do que o índice do node de B;
        - se não existir (node de B é maior que todos de A), o target é o menor índice de A.

    Resultado: para cada node da stack B sabemos onde ele deve cair na stack A.

    Variáveis:

        - tmp → percorre os nós de B, um a um.
        - target → resultado devolvido pela ft_target, que diz “a posição em A onde este nó de B deve entrar”.
        - pos (em cada nó) → foi escrito em A e B pela ft_position e serve para saber a posição atual (0=topo, 1, 2, …).
        - target (em cada nó de B) → será preenchido aqui e indica onde esse nó vai cair em A.


    > Atualização das posições: 

    ft_position(stack_a);  // escreve pos = 0,1,2,… em cada node da stack A
    ft_position(stack_b);  // escreve pos = 0,1,2,… em cada node da stack B

    Stack A (topo→base):     Stack B (topo→base):
    
    [ idx=3 | pos=0 ]        [ idx=9 | pos=0 ]
    [ idx=12| pos=1 ]        [ idx=1 | pos=1 ]
    [ idx=20| pos=2 ]        [ idx=15| pos=2 ]

    
    > Percorre os nodes da stack B:

    tmp = *stack_b;
    while (tmp) 
    {
        target = ft_target(stack_a, tmp->index, INT_MAX, target);
        tmp->target = target;
        tmp = tmp->next;
    }

    Para cada node da stack B, chama a função ft_target() e passa:

        - a stack A.
        - o indice do node da stack B que estamos (tmp->index).
        - INT_MAX (indica que não temos candidato incial).
        - target (target_pos), que é a posição da stack A onde esse node deve ser inserido.
        
    Armazena o target: tmp->target = target.

    
    Exemplo em execução

    Stack A (topo→base):     Stack B (topo→base):
    
    [ idx=3 | pos=0 ]        [ idx=9 | pos=0 ]
    [ idx=12| pos=1 ]        [ idx=1 | pos=1 ]
    [ idx=20| pos=2 ]        [ idx=15| pos=2 ]

    Iteração 1: node da stack B com idx=9

    Chamada: target = ft_target(A, b_index=9, target_index=INT_MAX, target_pos=0)

    A0: 3 > 9? não.
    A1: 12 > 9? sim && 12 < INT_MAX → candidato (i = 12, pos = 1).
    A2: 20 > 9? sim && 20 < 12? não → mantém.

    Encontrou o sucessor = 12 (pos = 1).
    Retorna target = 1.
    → Grava na stack B: [idx=9 | pos=0 | target=1]

    Iteração 2: node da stack B com idx = 1

    Chamada: target = ft_target(A, b_index=1, target_index=INT_MAX, target_pos=0)

    A0: 3 > 1? sim && 3 < INT_MAX → candidato (i = 3, pos = 0).
    A1: 12 > 1? sim && 12 < 3? não.
    A2: 20 > 1? sim && 20 < 3? não.

    Successor = 3 (pos = 0).
    Retorna target = 0.
    → Grava na stack B: [idx=1 | pos=1 | target=0]
    
    Iteração 3: node da stack B com idx = 15

    Chamada: target = ft_target(A, b_index=15, target_index=INT_MAX, target_pos=0)

    A0: 3 > 15? não.
    A1: 12 > 15? não.
    A2: 20 > 15? sim && 20 < INT_MAX → candidato (i = 20, pos = 2).

    Successor = 20 (pos = 2).
    Retorna target = 2.
    → Grava na stack B: [idx=15 | pos=2 | target=2]

    Resultado final depois de ft_assign_pos

    Agora cada nó de B sabe exatamente onde deve cair em A:

    Stack B:
    
    [ idx=9  | pos=0 | target=1 ]  → o node com indice 9 deve cair antes do node com indice 12 na stack A
    [ idx=1  | pos=1 | target=0 ]  → o node com indce 1 deve cair antes do node com indice 3 na stack A
    [ idx=15 | pos=2 | target=2 ]  → o node com indice 15 deve cair antes do node de indice 20 na stack A

    

    
    > ft_cost(a, b)

    void	ft_cost(t_stack **stack_a, t_stack **stack_b)
    {
	    t_stack	*b_tmp;
	    int		a_size;
	    int		b_size;

	    a_size = ft_size(*stack_a);     // tamanho atual da stack A
	    b_size = ft_size(*stack_b);     // tamanho atual da stack B
	    b_tmp = *stack_b;               // começamos no head/topo da stack B
        
	    while (b_tmp)                   // percorremos a stack B
	    {
		    b_tmp->cost_b = b_tmp->pos;  // custo base: pos rotações normais (rb)
		    if (b_tmp->pos > b_size / 2) // se estiver na metade de baixo
			    b_tmp->cost_b = (b_size - b_tmp->pos) * -1;  // o custo é negativo e vai ser mais barato fazer rrb
                
		    b_tmp->cost_a = b_tmp->target;  // custo base: target rotações normais (ra)
		    if (b_tmp->target > a_size / 2)  // se o alvo estiver na metade de baixo 
			    b_tmp->cost_a = (a_size - b_tmp->target) * -1;  // o custo é negativo e vai ser mais barato fazer rra
                
		    b_tmp = b_tmp->next;    // avança para o próximo node da stack B
	    }
    }

    COmo vimos, na função ft_target(), para um node que está na stack B com índice b_index, queremos saber em que posição
    na stack A (target_pos) ele deve entrar para manter a stack A ordenada, por índice:

        - Se existir na stack A alguém com índice maior do que b_index, escolhe o menor desses (o successor) e devolve a posição dele.
        - Se não existir (ou seja, b_index é maior do que todos os índices atualmente na stack A), devolve a posição do menor índice de A 
          (ordem circular → “entra antes do menor”).

    A ft_target usa a posição dos nodes da stack A para devolver um número (não um ponteiro) que é o target_pos, para que
    a função ft_cost() calcule quantas rotações a stack A precisa (ra/rra) para colocar esse node no topo, antes de fazer pa.

    Vimos que cada node tem a sua posição (pos) e que, na função ft_assign_pos(), para cada node da stack B, sabemos o seu target (posição na stack A 
    onde esse node de B deve entrar).

    Para cada node da stack B sabemos o cost_a e o cost_b.

    A função ft_cost() transforma a posição e o target em números de rotações com sinal:

        - cost_b: quantas rotações na stack B para trazer o node ao topo.
        - cost_a: quantas rotações na stack A para colocar o alvo (target) no topo.

    Durante a reinserção (trazer elementos de volta da stack B para a stack A), para cada node da stack B queremos saber: 
        
        - Quantas rotações na stack B para colocá-lo no topo?
              
          Para trazer um node ao topo, sabemos exatamente quantas rotações normais precisamos.
          Para decidir rotação normal vs rotação inversa, comparamos a posição com o meio da stack.

          Na função ft_cost(), para cada node da stack B, calculamos quantas rotações são precisas para alinhar a stack:
          
            > B (para trazer o node ao topo): 

            → Se a posição do node na stack B (pos_b) estiver na metade de cima (pos_b <= size_b / 2) → cost_b = + pos_b ,
             pelo o que é mais barato fazer "rb", "pos_b" vezes;
            → se a posição do node na stack B (pos_b) se estiver na metade de baixo (pos_b > size_b / 2) → cost_b = - (size_b - pos_b) ,
             pelo o que é mais barato fazer "rrb", "(size_b - pos_b)" vezes.

            Supondo que estamos a processar um node da stack B (b_tmp),

                > b_tmp->cost_b = b_tmp->pos;

                  Ideia: se trouxermos este node ao topo da stack B só com rotações normais (rb), quantas precisamos?
                  Resposta: pos vezes.
                  Sinal positivo ⇒ usamos rb.

                > if (b_tmp->pos > b_size / 2)   ->   "A posição pos passou da metade ?"
                    b_tmp->cost_b = (b_size - b_tmp->pos) * -1;

                  Caso o node esteja na metade de baixo da stack B, são necessárias b_size - pos rotações inversas (rrb).
                  Sinal negativo => usamos rrb.
                  
            > A (para alinhar o target no topo - usamos o target calculado para aquele node da stack B, para saber em que posição o node de B deve entrar):

            → Se o target do node da stack B na stack A (target) estiver na metade de cima (target <= size_a / 2) → cost_a = + target ,
              pelo o que é mais barato fazer "ra", "target" vezes.
            → Se o target do node da stack B na stack A (target) estiver na metade de baixo (target > size_a / 2) → cost_a = - (size_a - target) ,
              pelo o que é mais barato fazer "rra", "(size_a - target)" vezes.

                > b_tmp->cost_a = b_tmp->target;

                  Ideia: para inserir o node da stack B na stack A no local certo, precisamos de alinhar a stack A para que o target (posição-alvo) vá ao topo.
                  Se for só com rotações normais (ra), precisamos de target vezes.
                  Sinal positivo ⇒ usamos ra.

                > if (b_tmp->target > a_size / 2)
                    b_tmp->cost_a = (a_size - b_tmp->target) * -1;

                  Caso o target do node da stack B na stack A esteja na metade inferior, são necessárias (a_size - target) rotações inversas (rra).
                  Sinal negativo ⇒ usamos rra.
              
            Ou seja, se pos > size / 2, normalmente é mais barato fazer rotações inversas (size - pos vezes), caso contrário, se pos <= size / 2,
            é mais barato fazer rotações normais (pos vezes).

                Ex.: topo já é 0 → 0 rotações; se for 3 → 3 rotações normais.

                O sinal (+ / -) permite, depois, combinar rotações: - mesmo sinal → dá para usar rr (ambos +) ou rrr (ambos -), na função ft_cheapest(),
                                                                      para rodar as duas stacks ao mesmo tempo, reduzindo o número de instruções.

            
            Exemplo: Estado (pos e target já calculados por ft_position + ft_assign_pos)

                     a_size = 7 (posições 0..6; metade inteira = 3)
                     b_size = 5 (posições 0..4; metade inteira = 2)

                     Nodes na stack B (topo→base)
                     
                     Node	 pos em B	 target em A	               Explicação do target
                      b0	     0	         4	        b0 deve cair antes do node que está na pos 4 da stack A
                      b1	     1	         0	        b1 deve cair no início (antes do menor na stack A)
                      b2	     4	         6	        b2 deve cair antes no node que está na pos 6 da stack A.
                      b3	     3	         2	        node mais para baixo; alvo na metade de cima


                      Calcular cost_b (B) e cost_a (A)

                      Metades:  B: b_size / 2 = 2 ⇒ pos 0..2 “metade de cima”; 
                                                    pos 3..4 “metade de baixo”;
                                A: a_size/2 = 3 ⇒ target 0..3 “metade de cima”; 
                                                  target 4..6 “metade de baixo”;

                      Node	  pos	     Regra em B	               cost_b	    target	            Regra em A	            cost_a
                       b0	   0	  0 ≤ 2 → +pos (rb 0x)	         +0	          4	        4 > 3 → -(7-4)= -3 (rra 3x)	      -3
                       b1	   1	  1 ≤ 2 → +pos (rb 1x)	         +1	          0	        0 ≤ 3 → +target (ra 0x)	          +0
                       b2	   4	  4 > 2 → -(5-4)= -1 (rrb 1x)	 -1	          6	        6 > 3 → -(7-6)= -1 (rra 1x)	      -1
                       b3	   3	  3 > 2 → -(5-3)= -2 (rrb 2x)	 -2	          2	        2 ≤ 3 → +target (ra 2x)	          +2

    A função ft_cost() preenche os campos cost_a e cost_b em cada node da stack B.
    A função ft_cheapest() depois vai ler esses campos em todos os nodes da stack B e calcula abs(cost_a) + abs(cost_b) e escolhe o node com
    o menor valor.
    Em seguida chama a função ft_best_move() com esses dois custos, e ele: - usa rr se cost_a > 0 && cost_b > 0;
                                                                           - usa rrr se cost_a < 0 && cost_b < 0;
                                                                           - depois completa o que faltar com ra/rra e rb/rrb;
                                                                           - e no fim faz pa.


    
    > ft_cheapest(a, b)

    void	ft_cheapest(t_stack **stack_a, t_stack **stack_b)
    {
	    t_stack	*tmp;
	    int		cheapest;   // melhor custo total visto até agora (soma dos absolutos)
	    int		a_cost;     // cost_a do candidato (com sinal)
	    int		b_cost;     // cost_b do candidato (com sinal)

	    a_cost = 0;         // começamos com 0 pois ainda não encontrarmos nenhum candidato
	    b_cost = 0;         // começamos com 0 pois ainda não encontrarmos nenhum candidato
        
	    if (!*stack_b)    // se a stack B está vazia, não há para para reinserir na stack A
		    return ;
            
	    tmp = *stack_b;      // começamos no head/topo da stack B
	    cheapest = INT_MAX;  // nenhum candidato visto até agora
        
	    while (tmp)          // percorre todos os nodes da stack B
	    {
		    if (ft_abs(tmp->cost_a) + ft_abs(tmp->cost_b) < cheapest)   // Para cada node de B calculamos o custo total e verificamos se é o mais barato (o melhor visto)
		    {
			    cheapest = ft_abs(tmp->cost_b) + ft_abs(tmp->cost_a);   // se for o melhor custo total é guardado em cheapest e torna-se o melhor visto até agora
			    a_cost = tmp->cost_a;                                   // guarda o cost_a com sinal em a_cost (ra vs rra)
			    b_cost = tmp->cost_b;                                   // guarda o cost_b com sinal em b_cost (rb vs rrb)
		    }
		    tmp = tmp->next;
	    }
        
	    if (cheapest != INT_MAX)  // se houve pelo menos um candidato ...
		    ft_best_move(stack_a, stack_b, a_cost, b_cost);  // executa os movimentos ideais e faz pa
	    else
		    return ;
    }

    Antes de chegarmos À função ft_cheapest() fizemos em cada iteração do loop principal de reinserção:

        - ft_position(A) e ft_position(B) → cada node tem a sua posição pos atualizada.
        - ft_assign_pos(A,B) → para cada node da stack B, foi escrito o target (posição na stack A onde esse node deve entrar).
        - ft_cost(A,B) → para cada node da stack B:
        
            - cost_b: quantas rotações (rb ou rrb) na stack B são precisas para colocar esse node no topo (sinal: + → rb, - → rrb);
            - cost_a: quantas rotações (ra ou rra) na stack A são precisas para alinhar a posição target desse node no topo (sinal: + → ra, - → rra).

    Agora a função ft_cheapest() escolhe qual o node da stack B vamos reinserir já na stack A, utilizando os custos calculados na ft_cost().
    Assim, o node da stack B com o custo total mais baixo vai ser o primeiro a ser reinserido na stack A.

    Depois de escolhermos o mais barato, a função chama a função ft_best_move() para executar as rotações da forma mais eficiente (utilizando 
    rr/rrr quando puder) e por fim, fazer pa. 

    
    > a_cost e b_cost: guardam os custos (com sinal) do candidato vencedor. Começam com 0, pois ainda não há um candidato vencedor. 
                       Assim que o primeiro node da stack B for avaliado, estes valores serão substituidos pelos custos do candidato vencedor.
                       Guardar com sinal é crucial: o sinal define a direção das rotações (normal vs inversa) e permite rr/rrr caso os sinais sejam iguais.

    > |cost_a| + |cost_b|: representa o cálculo do custo total.
                           Por que usamos o valor absoluto (ft_abs)? cost_a e cost_b têm sinal (direção) e magnitude (quantidade de rotações).
                           Para comparar os candidatos, interessa-nos primeiro a quantidade de instruções; a direção só importa na execução (para combinar rr/rrr).
                           Por isso comparamos |cost_a| + |cost_b|:

                                - |cost_a| = quantas ra/rra serão necessárias (independente do sentido),
                                - |cost_b| = quantas rb/rrb serão necessárias.

                           A soma dos absolutos dá-nos o número (aproximado) de quantos passos/instruções no total teremos de fazer para alinhar a stack A e a stack B, antes de 
                           fazermos pa. Serve apenas para eleger o melhor node da iteração atual.
                           Se for menor do que o melhor custo total visto até agora (cheapest), atualizamos o candidato vencedor:
                           
                                - cheapest recebe o novo total;
                                - copia os custos com sinal (a_cost e b_cost do candidato vencedor).
                                  O sinal é crítico para a execução (decidir rr/rrr vs rotações separadas).

    > if (cheapest != INT_MAX): Se houve pelo menos um node, chamamos a função ft_best_move() para executar:
    
        - rr: se a_cost e b_cost são ambos +; rrr: se são ambos -;
        - completa o que faltar na stack A (ra/rra) e na stack B (rb/rrb).
        - faz pa (insere o node do candidato vencedor na stack A na posição correta).




    Exemplo: Imaginemos na stack B (topo→base) com 4 nodes. Cada node já tem: - pos e target calculados anteriormente;
                                                                              - cost_a/cost_b calculados pela ft_cost.

    B topo
    ┌───────────────────────────────────────────────────────────┐
    │ [N0] cost_a=+3  cost_b=+0   → total = |+3|+|+0| = 3       │
    │ [N1] cost_a=+0  cost_b=+1   → total = |+0|+|+1| = 1   ★   │  ← (menor)
    │ [N2] cost_a=-1  cost_b=-1   → total = |-1|+|-1| = 2       │
    │ [N3] cost_a=+2  cost_b=-2   → total = |+2|+|-2| = 4       │
    └───────────────────────────────────────────────────────────┘
    B base


    A ft_cheapest() vai percorrer nesta ordem: N0 → N1 → N2 → N3.

    A cada node, compara |cost_a| + |cost_b| com cheapest, e se o custo total < cheapest, esse node torna-se o candidato vencedor
    atual e guardamos a_cost e b_cost dele (com sinal).

    Estado inicial:  
    
    cheapest = INT_MAX
    a_cost   = 0
    b_cost   = 0
    tmp → N0

    Iteração 1 (N0):

    total = |+3| + |+0| = 3
    3 < INT_MAX → sim → vencedor = N0
    cheapest = 3
    a_cost   = +3
    b_cost   = +0
    tmp->next → N1

    Iteração 2 (N1):

    total = |+0| + |+1| = 1
    1 < 3 → sim → vencedor = N1
    cheapest = 1
    a_cost   = +0
    b_cost   = +1
    tmp->next → N2

    Iteração 3 (N2):

    total = |-1| + |-1| = 2
    2 < 1 → não → mantém N1
    tmp->next → N3

    Iteração 4 (N3):

    total = |+2| + |-2| = 4
    4 < 1 → não → mantém N1
    tmp->next → NULL → fim do while

    Decisão final: cheapest != INT_MAX → sim
                   chama ft_best_move(A, B, a_cost=+0, b_cost=+1)


    
    
    > ft_best_move(stack_a, stack_b, a_cost, b_cost)

    void	ft_best_move(t_stack **stack_a, t_stack **stack_b, int a_cost,
		    int b_cost)
    {
	    if (a_cost < 0 && b_cost < 0)
	    	rev_rotate_both(stack_a, stack_b, &a_cost, &b_cost);
	    else if (a_cost > 0 && b_cost > 0)
	    	rotate_both(stack_a, stack_b, &a_cost, &b_cost);
	    rotate_a(stack_a, &a_cost);
	    rotate_b(stack_b, &b_cost);
	    ft_pa(stack_a, stack_b);
    }


    > a_cost: nº de rotações para alinhar a posição target na stack A no topo.
    
        > 0 → fazer ra esse nº de vezes
        < 0 → fazer rra -(a_cost) vezes

    > b_cost: nº de rotações para colocar o node escolhido da stack B no topo.

        > 0 → fazer rb esse nº de vezes
        < 0 → fazer rrb -(b_cost) vezes

    > Os sinais importam porque permitem combinar:

        a_cost > 0 && b_cost > 0 → usar rr (ra + rb juntos)
        a_cost < 0 && b_cost < 0 → usar rrr (rra + rrb juntos)


    > Mesma direção para baixo? (a_cost < 0 e b_cost < 0) → rev_rotate_both vai fazer rrr enquanto puder e aproximar ambos de 0.

    > Mesma direção para cima? (a_cost > 0 e b_cost > 0) → rotate_both vai fazer rr enquanto puder e aproximar ambos de 0.

    Depois: - rotate_a termina o resto de a_cost (se ainda não for 0): ra ou rra consoante o sinal;
            - rotate_b termina o resto de b_cost (idem com rb ou rrb);
            - Finalmente pa: traz o topo de B para o topo de A (agora no lugar certo).


    static void	rev_rotate_both(t_stack **stack_a, t_stack **stack_b, int *a_cost,
	    	int *b_cost)
    {
	    while (*a_cost < 0 && *b_cost < 0)
	    {
		    (*a_cost)++;     // incrementar um nº negativo aproxima de 0
		    (*b_cost)++;
		    ft_rrr(stack_a, stack_b);
	    }
    }

    Porque incrementa?

    Se o custo é negativo, cada rrr consome 1 rotação inversa simultânea em A e B;
    Logo, para “andar” o contador negativo para o zero, faz-se ++ (-3 → -2 → -1 → 0).

    Exemplo com contagens:
    
    a_cost = -3, b_cost = -2

    rrr → a_cost = -2, b_cost = -1
    rrr → a_cost = -1, b_cost = 0
    acabaram as simultâneas (b chegou a 0); sai



    static void	rotate_both(t_stack **stack_a, t_stack **stack_b, int *a_cost,
	    	int *b_cost)
    {
	    while (*a_cost > 0 && *b_cost > 0)
	    {
		    (*a_cost)--;   // decrementar um nº positivo aproxima de zero
		    (*b_cost)--;
		    ft_rr(stack_a, stack_b);
	    }
    }

    Porque decrementa?

    Se o custo é positivo, cada rr consome 1 rotação normal simultânea;
    Para “gastar” o custo até 0 → --.

    Exemplo com contagens: 

    a_cost = +2, b_cost = +4

    rr → a_cost = +1, b_cost = +3
    rr → a_cost = +0, b_cost = +2  (acabaram as simultâneas)

    Exemplos: 

    (A) Sinais iguais positivos (usa rr)

    Entrada: a_cost = +3, b_cost = +1
    
    Passo 1 (rotate_both):  rr → a_cost = +2, b_cost = 0   (acabou a simultânea)
    Passo 2 (rotate_a): ra, ra (a_cost → 0)
    Passo 3 (rotate_b): nada (b_cost já é 0)
    Passo 4 pa

    Operações totais: rr, ra, ra, pa

    
    (B) Sinais iguais negativos (usa rrr)

    Entrada: a_cost = -2, b_cost = -5

    Passo 1 (rev_rotate_both):  rrr → a_cost = -1, b_cost = -4
                                rrr → a_cost = 0, b_cost = -3
    Passo 2 (rotate_a): nada
    Passo 3 (rotate_b): rrb, rrb, rrb (b_cost → 0)
    Passo 4 pa

    Operações: rrr, rrr, rrb, rrb, rrb, pa


    static void	rotate_a(t_stack **stack_a, int *cost)
    {
	    while (*cost)   // enquanto ainda houver rotações por fazer...
	    {
		    if (*cost > 0)  // Se o custo for positivo
		    {
			    ft_ra(stack_a);  // roda a stack A para cima (o topo/head vai para a base)
			    (*cost)--;       // consome uma rotação
		    }
		    else
		    {
			    ft_rra(stack_a);
			    (*cost)++;
		    }
	    }
    }

    t_stack **stack_a → Aponta para a stack A (precisamos de ** porque ft_ra e ft_rra podem alterar o head, o topo da linked list).

    int *cost → Um contador de rotações que indica quantas operações ainda faltam para alinhar a posição do target na stack A.
    
        - Se for positivo → faltam rotações normais (ra).
        
          Ex: Se cost = 3, quer dizer que temos de rodar 3 vezes para cima (ra).
              A cada iteração fazemos ra.
              Subtraímos 1: 3 -> 2 -> 1 -> 0.
              QUando chega a 0, o target já está no topo.
        
        - Se for negativo → faltam rotações inversas (rra).
        
          Ex: Se cost = -2, quer dizer que temos de rodar 2 vezes para baixo (rra).
              A cada iteração fazemos rra.
              Somamos 1: -2 -> -1 -> 0
              Quando chega a 0, o target já está no topo.

        - Se for 0 → já está alinhado, não há nada a fazer.
        

    
    Exemplo 1: cost = +2 , o que significa: 2 rotações normais (ra) para alinhar.

    Stack Inicial: A -> [4] -> [8] -> [15] -> [23] -> [42] -> NULL

    Iteração 1: ra → A -> [8] -> [15] -> [23] -> [42] -> [4] -> NULL
    cost = 2 → 1

    Iteração 2: ra → A -> [15] -> [23] -> [42] -> [4] -> [8] -> NULL
    cost = 1 → 0

    
    Exemplo 2: cost = -2

    Significa: 2 rotações inversas (rra) para alinhar.

    Stack Inicial: A -> [4] -> [8] -> [15] -> [23] -> [42] -> NULL

    Iteração 1: rra → A -> [42] -> [4] -> [8] -> [15] -> [23] -> NULL
    cost = -2 → -1

    Iteração 2: rra → A -> [23] -> [42] -> [4] -> [8] -> [15] -> NULL
    cost = -1 → 0

      
    static void	rotate_b(t_stack **stack_b, int *b_cost)
    {
	    while (*b_cost)
	    {
		    if (*b_cost > 0)
		    {
			    ft_rb(stack_b);
			    (*b_cost)--;
		    }
		    else
		    {
			    ft_rrb(stack_b);
			    (*b_cost)++;
		    }
	    }
    }

    A função rotate_b() é exatamente igual a rotate_a(), mas aplicada à stack B (rb e rrb em vez de ra/rra).


    

    Exemplo 1 — cost_a positivo (usa ra)
    
    Estado inicial (após ft_position e ft_assign_pos)

    A (topo→base, a_size = 5):    [i=3 | p=0] → [i=8 | p=1] → [i=12 | p=2 ] → [i=20 | p=3] → [i=27 | p=4] → NULL
                                       A0            A1             A2              A3             A4

    B (topo→base, b_size = 3):    [i=9 | p=0 | tg=?] → [i=15 | p=1 | tg=?] → [i=1 | p=2 | target=?] → NULL
                                         B0                    B1                   B2


    Suponhamos que estamos a avaliar o node B0 (topo da stack B), com index = 9.
    A função ft_target(&A, b_index=9, ...):  

    Passagem 1 (procurar successor)

      Frame 1
      tmp = A0 → tmp->index = 3
      Condição: 3 > 9? não → ignora
      tmp = tmp->next → A1

      Frame 2
      tmp = A1 → tmp->index = 8
      8 > 9? não → ignora
      tmp = tmp->next -> A2

      Frame 3
      tmp = A2 → tmp->index = 12
      12 > 9? sim e 12 < target_index (INT_MAX)? sim → match
      Atualiza: target_index = 12, target_pos = 2
      tmp = tmp->next -> A3

      Frame 4
      tmp = A3 → tmp->index = 20
      20 > 9? sim mas 20 < 12? não → mantém (12, pos=2)
      tmp = NULL → acabou a 1ª passagem.

      Como target_index != INT_MAX → retorna target_pos = 2.

      A função ft_target() devolveu target_pos = 2 (porque o sucessor na stack A é o 12, que está na posição 2).

      O que fazer com 2? Queremos pôr o node da stack B (i=9) antes do node da stack A, com i=12.
      
      Logo depois da função ft_assign_pos, o node B0 fica:  B0: [i=9 | p=0 | tg=2]

    A função ft_cost() calcula os custos:

        > Para cada node da stack B (aqui foquemos no B0):

            - para B: cost_b depende da pos=0 com b_size=3

            - pos <= b_size/2 → cost_b = +pos = +0 (já está no topo de B)

        > para A: cost_a depende de target=2 com a_size=5

            - target <= a_size/2 (2 <= 2) → cost_a = +target = +2 ⇒ vamos usar ra duas vezes

    Para o node B0: cost_b = +0  (nada em B)
                    cost_a = +2  (2x ra)

    Se o candidato vencedor da função ft_cheapest() for B0, então ft_best_move() acabará por chamar rotate_a(A, &cost_a) com cost_a = +2.
    A função rotate_a alinha a posição target do node B0 no topo:

    Estado anterior: stack A: [i=3 | p=0] → [i=8 | p=1] → [i=12 | 2] → [i=20 | p=3] → [i=27 | p=4] → NULL
    cost_a = +2

    Iteração 1 (cost_a > 0 => ra): A -> [i=8 | p=0] → [i=12 | p=1] → [i=20 | p=2] → [i=27 | p=3] → [i=3 | p=4] → NULL
    cost_a: 2 → 1
                                   
    Iteração 2 (cost_a > 0 => ra): A -> [i=12 | p=0] → [i=20 | p=1] → [i=27 | p=2] → [i=3 | p=3] → [i=8 | p=4] → NULL
    cost_a chegou a 0

    O target (posição 2 original, onde estava o node com indice 12) está agora no topo.
    Isto significa que quando fizermos pa, o node da stack B (com indice 9) cairá antes do node com indice 12.

    Onde entra a função rotate_b() ? A função rotate_b() é idêntico à função rotate_a(), mas trabalha na stack B com rb/rrb:

        - A função coloca no topo/head da stack B o node do candidato vencedor (aquele escolhido pela função ft_cheapest).
        
    Depois que as stacks A e B estão alinhadas (target no topo da stack A e o candidato vencedor no topo da stack B), fazemos
    pa para inserir o node no lugar certo da stack A.


    
    > ft_stack_shift(a) — Alinhamento final (menor no topo)

    static void	ft_stack_shift(t_stack **stack_a)
    {
	    int	size;
	    int	lowest;

	    size = ft_size(*stack_a);            // nº de nodes da stack A
	    lowest = ft_lowest_idx_pos(stack_a);  // posição do menor indice
        
	    if (lowest > size / 2)          // verifica se a posição do menor indice está na metade de baixo
	    {
		    while (lowest < size)      
		    {
			    ft_rra(stack_a);    // faz rra até o menor subir ao topo
			    lowest++;
		    }
	    }
	    else                           // se a posição do menor indice estiver na metade de cima
	    {
		    while (lowest)
		    {
			    ft_ra(stack_a);         // faz ra até o menor ir para o topo
			    lowest--;
		    }
	    }
    }

    Esta é a etapa final: a função ft_stack_shift() vai garantir que a stack A fica ordenada (isto é, com o menor índice no topo).
    Até aqui, a stack A estava ordenada circularmente, ou seja, em ordem crescente por indice, em que o menor index (index = 0) pode
    não estar no topo.

    O objetivo aqui é colocar o node com menor indice no topo da stack A, com o minimo de rotações.
    
    Se a posição do node com menor indice (lowest) estiver na segunda metade da stack, ou seja, a metade de baixo (lowest > size/2) -> é mais barato 
    fazer rra para fazer com que esse node suba até ao topo. Cada rra sobe o node do fim para o topo e, na contagem, aproxima lowest de size. QUando
    lowest == size, quer dizer que subimos size - original lowest vezes - o menor ficou no topo.
    
    Caso contrário, se a posição do node com menor indice (lowest) estiver na primeira metade da stack (metade de cima) -> é mais barato fazer ra 
    para fazer com que esse node vá para o topo. Cada ra desce o topo para a base, o menor sobe 1 posição e lowest aproxima-se de 0.
    QUando lowest == 0, quer dizer que o menor chegou ao topo.

    

    int	ft_lowest_idx_pos(t_stack **stack)
    {
	    t_stack	*tmp;
	    int		lowest_i;
	    int		lowest_p;

	    tmp = *stack;             // começamos no head/topo da stack A
	    lowest_i = INT_MAX;       // ainda não foi encontrado nenhum indice que seja o menor até agora
	    ft_positon(stack);        // atualizamos a posição
	    lowest_p = tmp->pos;      // iniciamos com a posição do topo (0)
        
	    while (tmp)               // percorremos a stack A
	    {
		    if (tmp->index < lowest_i)       // se o indice do node da stack A for o menor até agora
		    {
			    lowest_i = tmp->index;       // atualizamos como o menor indice encontrado até agora
			    lowest_p = tmp->pos;         // guardamos a posição dele
		    }
		    tmp = tmp->next;                 // avançamos para o próximo node
	    }
	    return (lowest_p);                    // devolve a posição do menor
    }

    
    
    Exemplo A — usar ra

    A (size=5):
    
    A: [i=5 | p=0] → [i=7 | p=1] → [i=0 | p=2] → [i=9 | p=3] → [i=12 | p=4]

    lowest = 2   (menor índice=0 está na pos 2)
    size/2 = 4/2 = 2
    
    lowest <= size/2 → está na primeira metade da stack A -> size - lowest = 4 - 2 -> usa ra (2 vezes)
    
    1ª iteração: ra → A: [i=7 | p=0] → [i=0 | p=1] → [i=9 | p=2] → [i=12 | p=3] → [i=5 | p=4]
    lowest: 2→1

    2ª iteração: ra → A: [i=0 | p=0] → [i=9 | p=1] → [i=12 | p=2] → [i=5 | p=3] → [i=7 | p=4]
    lowest: 1 -> 0

    O while parou -> o menor (lowest original p = 2, e i = 0) está no topo.


    Exemplo B — usar rra

    A (size=6):

    A: [i=5 | p=0] → [i=7 | p=1] → [i=8 | p=2] → [i=9 | p=3] → [i=12 | p=4] → [i=0 | p=5]

    lowest = 5   (menor=0 está na pos 5)
    size/2 = 6/2 = 3
    
    lowest > size/2 → está na segunda metade da stack A -> size - lowest = 6 - 5 = 1 -> usa rra 1 vez

    1ª iteração: rra ->  [i=0 | p=0] → [i=5 | p=1] → [i=7 | p=2] → [i=8 | p=3] → [i=9 | p=4] → [i=12 | p=5]

    O while parou -> o menor (lowest original p = 5 e i = 0) está no topo.
























