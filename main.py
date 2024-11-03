import tkinter as tk
from tkinter import messagebox
import subprocess

def gerar_chaves():
    try:
        p = int(entry_p.get())
        q = int(entry_q.get())
        e = int(entry_e.get())
        mensagem = entry_mensagem.get()

        # Chama o executável C e passa os parâmetros
        process = subprocess.Popen(['./criptografia'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        
        # Envia os dados para o programa C
        input_data = f"gerar\n{p}\n{q}\n{e}\n{mensagem}\n"
        stdout, stderr = process.communicate(input=input_data)
        
        if stderr:
            messagebox.showerror("Erro", stderr)
        else:
            messagebox.showinfo("Resultado", stdout)

    except ValueError:
        messagebox.showerror("Erro", "Por favor, insira números válidos.")

def descriptografar():
    try:
        d = int(entry_d.get())
        n = int(entry_n.get())
        valores_criptografados = entry_criptografados.get()

        # Chama o executável C para descriptografar
        process = subprocess.Popen(['./criptografia'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

        # Envia os dados para o programa C
        input_data = f"descriptografar\n{d}\n{n}\n{valores_criptografados}\n"
        stdout, stderr = process.communicate(input=input_data)
        
        if stderr:
            messagebox.showerror("Erro", stderr)
        else:
            messagebox.showinfo("Mensagem Descriptografada", stdout)

    except ValueError:
        messagebox.showerror("Erro", "Por favor, insira números válidos.")

# Criação da interface gráfica
root = tk.Tk()
root.title("Criptografia")

# Gerar Chaves
tk.Label(root, text="Número primo p:").pack()
entry_p = tk.Entry(root)
entry_p.pack()

tk.Label(root, text="Número primo q:").pack()
entry_q = tk.Entry(root)
entry_q.pack()

tk.Label(root, text="Número e:").pack()
entry_e = tk.Entry(root)
entry_e.pack()

tk.Label(root, text="Mensagem:").pack()
entry_mensagem = tk.Entry(root)
entry_mensagem.pack()

botao_gerar = tk.Button(root, text="Gerar Chaves e Criptografar", command=gerar_chaves)
botao_gerar.pack()

# Descriptografar
tk.Label(root, text="Chave privada d:").pack()
entry_d = tk.Entry(root)
entry_d.pack()

tk.Label(root, text="n (produto de p e q):").pack()
entry_n = tk.Entry(root)
entry_n.pack()

tk.Label(root, text="Valores criptografados:").pack()
entry_criptografados = tk.Entry(root)
entry_criptografados.pack()

botao_descriptografar = tk.Button(root, text="Descriptografar", command=descriptografar)
botao_descriptografar.pack()

root.mainloop()
