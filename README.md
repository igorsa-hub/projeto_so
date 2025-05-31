# ⚙ Simulador de paginação

Programa em **C** que simula a **paginação de memória**, incluindo a geração de **endereços virtuais**
e a conversão destes endereços para **endereços físicos**.

### 🛠 Compilação e execução

Para executar o programa, é necessário rodar o seguinte comando no diretório em que os arquivos
se encontram:

```bash
gcc -o main *.c
```

Em seguida, basta **executar** o arquivo recém-criado com os seguintes argumentos:

```bash
./main <Número de frames> <Número de endereços> <Número de processos> <Tempo de ciclo>
```

#### 📚 Dicionário de argumentos
| Argumento | O que significa |
| ---- | ----|
| `<Número de frames>` | **Número de frames** presentes na memória |
| `<Número de endereços>` | **Número de endereços** presentes em uma página |
| `<Número de processos>` | **Número de processos** presentes no sistema |
| `<Tempo de ciclo>` | **Tempo** (em segundos) que cada ciclo leva para ser atualizado |

### 🍻 Integrantes do grupo

| Nome  | Registro acadêmico |
| ------------- | :-------------: |
| Andrey Bezerra Virginio dos Santos | 10420696 |
| Igor Silva Araujo | 10428505 |
| Julia Vitoria Bomfim do Nascimento | 10425604 |
| William Saran dos Santos Junior  | 10420128 |
