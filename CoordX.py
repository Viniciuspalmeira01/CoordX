import turtle

# Função para converter coordenadas 3D em 2D (projeção isométrica)
def projecao_3d(x, y, z):
    # Conversão simples para 2D simulando perspectiva
    x2d = x - 0.5 * z
    y2d = y - 0.5 * z
    return x2d, y2d

# Função para desenhar um eixo
def desenhar_eixo(t, cor, x1, y1, x2, y2, nome):
    t.penup()
    t.goto(x1, y1)
    t.pendown()
    t.pencolor(cor)
    t.goto(x2, y2)
    t.penup()
    t.goto(x2, y2)
    t.write(" " + nome, font=("Arial", 10, "Arial"))

# Função para desenhar o vetor
def desenhar_vetor(t, x, y, z):
    x2d, y2d = projecao_3d(x, y, z)
    t.penup()
    t.goto(0, 0)
    t.pendown()
    t.pencolor("red")
    t.pensize(3)
    t.goto(x2d, y2d)
    t.write(f"  ({x}, {y}, {z})", font=("Arial", 15, "bold"))

# Entrada dos valores
x = float(input("Digite o valor de x: "))
y = float(input("Digite o valor de y: "))
z = float(input("Digite o valor de z: "))

# Configuração da janela
tela = turtle.Screen()
tela.title("Representação 3D de um Vetor (X, Y, Z)")
tela.bgcolor("white")

t = turtle.Turtle()
t.speed(0)

# Desenhar eixos
desenhar_eixo(t, "blue", 0, 0, 150, 0, "X")
desenhar_eixo(t, "green", 0, 0, 0, 150, "Y")
desenhar_eixo(t, "gray", 0, 0, -75, -75, "Z")

# Desenhar o vetor do usuário
desenhar_vetor(t, x, y, z)


turtle.done()
