import tkinter as tk
from tkinter import messagebox
import os

# Função para chamar o programa C e gerar uma chave
def gerar_chave():
    try:
        chave = os.popen("./rca_keygen generate").read().strip()
        entrada_chave.delete(0, tk.END)
        entrada_chave.insert(0, chave)
    except Exception as e:
        messagebox.showerror("Erro", f"Falha ao gerar chave: {e}")

# Função para encriptar uma mensagem usando a chave fornecida
def encriptar_mensagem():
    chave = entrada_chave.get()
    if not chave:
        messagebox.showwarning("Aviso", "Por favor, gere ou insira uma chave primeiro.")
        return
    
    try:
        mensagem_encriptada = os.popen(f"./rca_keygen encrypt {chave}").read().strip()
        entrada_encriptada.delete(0, tk.END)
        entrada_encriptada.insert(0, mensagem_encriptada)
    except Exception as e:
        messagebox.showerror("Erro", f"Falha ao encriptar a mensagem: {e}")

# Função para descriptografar a mensagem usando a chave fornecida
def descriptografar_mensagem():
    chave = entrada_chave.get()
    if not chave:
        messagebox.showwarning("Aviso", "Por favor, gere ou insira uma chave primeiro.")
        return
    
    try:
        mensagem_descriptografada = os.popen(f"./rca_keygen decrypt {chave}").read().strip()
        entrada_descriptografada.delete(0, tk.END)
        entrada_descriptografada.insert(0, mensagem_descriptografada)
    except Exception as e:
        messagebox.showerror("Erro", f"Falha ao descriptografar a mensagem: {e}")

# Configuração da janela principal
root = tk.Tk()
root.title("Gerador, Encriptador e Descriptografador de Chave RCA")

# Seção de Geração de Chave
botao_gerar = tk.Button(root, text="Gerar Chave RCA", command=gerar_chave)
botao_gerar.grid(row=0, column=0, padx=10, pady=10)

entrada_chave = tk.Entry(root, width=30)
entrada_chave.grid(row=0, column=1, padx=10, pady=10)

# Seção de Encriptação
botao_encriptar = tk.Button(root, text="Encriptar Mensagem", command=encriptar_mensagem)
botao_encriptar.grid(row=1, column=0, padx=10, pady=10)

entrada_encriptada = tk.Entry(root, width=30)
entrada_encriptada.grid(row=1, column=1, padx=10, pady=10)

# Seção de Descriptografia
botao_descriptografar = tk.Button(root, text="Descriptografar Mensagem", command=descriptografar_mensagem)
botao_descriptografar.grid(row=2, column=0, padx=10, pady=10)

entrada_descriptografada = tk.Entry(root, width=30)
entrada_descriptografada.grid(row=2, column=1, padx=10, pady=10)

# Inicia o loop principal da interface
root.mainloop()
