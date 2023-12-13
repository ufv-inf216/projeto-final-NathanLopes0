# DPI Bullet Hell
DPI Bullet Hell é um jogo onde o jogador é um aluno tentando passar pelas matérias do curso de Ciência da Computação para se formar.
## Mecânicas Básicas
O jogo é um "Bullet Hell", com um formato parecido com jogos de nave antigos, exceto que a nave é um aluno e o boss são professores do DPI. Além disso, ele não tem um número de Vidas e sim, uma ***Nota***, que começa em 40 a cada fase. Os projéteis dos alunos são ***Dúvidas*** que eles jogam nos professores que aumentam sua Nota. Ser acertado diminui sua Nota. Depois de receber muitas Dúvidas, os professores jogam ***Pontos Extras*** no aluno que pode ser coletado e guardado pra usar depois.

O aluno pode ser movido com as setas do teclado ou as teclas WASD, como o jogador preferir. A Barra de Espaço lança as Dúvidas, e a tecla B usa um dos Pontos Extras que o aluno tenha coletado para limpar a tela dos projéteis dos professores e ganhar aproximadamente 10 pontos, mas **fica sobrecarregado e não pode lançar Dúvidas por alguns segundos**.

## Condições de Vitória e Derrota
Um aluno passa de fase quando chega no fim do tempo da fase com nota maior ou igual a sessenta. Caso termine com menos, ele deve refazer a fase, e sua nota volta para a inicial (40).

Ele tem que passar de 3 provas (fases) de uma matéria pra passar dela por completo, então, por exemplo, depois que passar da fase do professor Ricardo 3 vezes, ele passará da matéria. Nessa demonstração há apenas 2 professores, e deve-se passar 3x de cada. As provas são intercaladas nessa demo, uma após a outra. Para aqueles que gostam de um desafio, depois que passarem das 3 provas o jogo continua com uma dificuldade maior, mas o objetivo principal é passar de 3. Haverá uma mensagem avisando quantas provas você já passou.

O jogo acaba em derrota se, a qualquer momento, sua nota chegar a 0. (O jogo fechará).

### Versão e Funcionalidades

Versão 0.1

Principais funcionalidades que devem ser testadas:

* Movimentação -> Velocidade do Jogador, Precisão do Movimento
* Colisão -> Colisões adequeadas
* Áudio -> Respostas de Colisão, Feedback de Acerto (no Jogador), Qualidade dos áudios, Volume
* Dificuldade -> Velocidade das "Balas" e Movimento das mesas, Limite de tela, Progressão de Dificuldade adequeada
* Artes -> Temática das artes, Qualidade da visualização (é possível distinguir o que é a arte no meio da gameplay?)