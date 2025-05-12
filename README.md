# Projeto loja de veiculos em C

## Como executar o projeto

1 - Clone o projeto
2 - Execute no terminal:

```terminal
gcc projeto.c -o projeto.exe
```

```terminal
projeto.exe
```

![veiculos1](https://github.com/user-attachments/assets/808d5a61-20c1-4924-8377-5d2d5c632048)


## Funcionalidades

### Listar veículos cadastrados

O sistema busca no arquivo veiculos.txt todos os registros e utilizando uma estrutura de dados FILA, cria a visualização de todos os veículos no arquivo.

O veículos serão listados da seguinte forma:

```
=== Veículos Cadastrados ===

Veículo 1:
Modelo: Corola
Marca: Toyota
Ano: 2023
Cor: Branco
Combustível: Gasolina
Status: Vendido
-------------------

Veículo 2:
Modelo: T-Cross
Marca: VW
Ano: 2021
Cor: Branco
Combustível: Gasolina
Status: Em estoque
-------------------

Veículo 3:
Modelo: Uno
Marca: Fiat
Ano: 1992
Cor: Vermelho
Combustível: Alcool
Status: Em estoque
-------------------
```

![veicullos2](https://github.com/user-attachments/assets/1c63385d-acbc-4951-827e-d2abc7154f35)


### Cadastrar veículos

O sistema permite o cadastro de novos veículo, no qual pede ao usuário que informe os dados do veículo e em seguida adiciona ao arquivo .txt os dados do novo veículo.

### Buscar veículos

O sistema nos permite buscar veículos pelo nome do modelo. Também é utilizada uma FILA para implementar o resultado da busca.

![veiculos3](https://github.com/user-attachments/assets/a00370ce-8251-4949-8579-4100ec0abcaf)
