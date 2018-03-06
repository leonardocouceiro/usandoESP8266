#define BUSCANDO_NOVA_PERGUNTA 0
#define AGUARDANDO_PERGUNTA 1
#define AGUARDANDO_RESPOSTA 2

int modo = BUSCANDO_NOVA_PERGUNTA;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  switch(modo) {
    case BUSCANDO_NOVA_PERGUNTA:
    // int status = http.GET
    // GET /desafios/1/perguntas/[1,2,3]

    // se receber
    // if(status == 200) {
    // parse JSON
    // exibir pergunta
    modo = AGUARDANDO_PERGUNTA;
    // delay    
    break;
    case AGUARDANDO_RESPOSTA:
    // jogar estrutura vinda do ArduinoJSON para LCD
    // monitorar botoes
    // se botao apertado
    // determina alternativa escolhida
    modo = ENVIANDO_RESPOSTA;
    break;

    case 
  }
}
