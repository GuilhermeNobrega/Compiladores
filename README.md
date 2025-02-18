<h2>📌 Estrutura de Arquivos</h2>
<p>Em projetos em C, é comum dividir o código entre:</p>
<ul>
    <li><strong>Arquivo <code>.h</code> (Header File)</strong>: Declarações de funções, macros, constantes e estruturas.</li>
    <li><strong>Arquivo <code>.c</code> (Source File)</strong>: Implementação das funções e, se necessário, variáveis.</li>
</ul>

<br>
<br>
<h2>🔧 Makefile: Automatizando a Compilação</h2>
<p>O <code>Makefile</code> evita a necessidade de compilar manualmente os arquivos toda vez.</p>

<h3>1️⃣ Definição de Variáveis</h3>
<pre><code>OBJECTS= ./build/compiler.o ./build/cprocess.o ./build/helpers/buffer.o ./build/helpers/vector.o
INCLUDES= -I./</code></pre>

OBJECTS: Contém os arquivos .o (objetos) gerados a partir dos arquivos .c.<br>
INCLUDES: Define o diretório de inclusão (-I./ significa que os .h estão na raiz do projeto).

<h3>2️⃣ Regra Principal (<code>all</code>)</h3>
<pre><code>all: ${OBJECTS}
gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./main</code></pre>
<ul>
    <li><code>all</code>: Alvo principal, depende dos arquivos objetos (<code>${OBJECTS}</code>).</li>
    <li><code>${OBJECTS}</code> contém todos os arquivos <code>.o</code> que foram previamente compilados a partir dos <code>.c</code>.</li>
    <li>Exemplo: <code>vector.c</code> vira <code>vector.o</code>, <code>buffer.c</code> vira <code>buffer.o</code>, etc.</li>
    <li>Esses arquivos <code>.o</code> são chamados de objetos compilados, mas ainda não formam um programa executável.</li>
    <li>O comando <code>gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./main</code> faz a linkagem, ou seja:</li>
    <ul>
        <li>Compila <code>main.c</code> junto com os arquivos <code>.o</code> de <code>buffer</code>, <code>vector</code> e outros.</li>
        <li>Inclui os cabeçalhos (<code>.h</code>) por meio de <code>#include</code>, garantindo que <code>main.c</code> tenha acesso às funções definidas nos <code>.c</code>.</li>
        <li>Gera o executável final (<code>./main</code>), que pode ser rodado diretamente no terminal.</li>
    </ul>
</ul>

<h3>3️⃣ Como Cada <code>.c</code> Vira um <code>.o</code></h3>
<pre><code>./build/compiler.o: ./compiler.c
gcc ./compiler.c ${INCLUDES} -o ./build/compiler.o -g -c</code></pre>
<ul>
    <li><code>./compiler.c</code> → transformado em <code>./build/compiler.o</code>.</li>
    <li><code>-c</code>: Gera código objeto sem linkar.</li>
</ul>

<h3>4️⃣ Regra <code>clean</code> (Limpeza)</h3>
<pre><code>clean:
rm ./main
rm -rf ${OBJECTS}</code></pre>
<ul>
    <li><code>rm ./main</code>: Apaga o executável.</li>
    <li><code>rm -rf ${OBJECTS}</code>: Remove todos os arquivos <code>.o</code> dentro de <code>build/</code>.</li>
</ul>

<h2>⚡ Executando o Makefile</h2>
<p>Para compilar o projeto, execute:</p>
<pre><code>make</code></pre>
<p>Para limpar os arquivos compilados, execute:</p>
<pre><code>make clean</code></pre>
