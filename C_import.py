import ctypes
import os


class Lib_C:
     def init (self,):
        self.arquivo_nome = "Matrizes.so" # Modulo com as funções C
        pass
    
     def importação(self):
     
        try:
          lib = ctypes.cdll.LoadLibrary(os.path.join(os.getcwd(), self.arquivo_nome))

        except OSError as e:
          print(f"Erro ao carregar a biblioteca {self.arquivo_nome}: {e}")
          print("Certifique-se de que o arquivo C foi compilado corretamente.")

          exit()
          return lib
     
     def main(self):
            
          lib = self.importação()
          lib.ortogonalidade.restype = ctypes.c_int  # Retorna int
          lib.ortogonalidade.argtypes = [
              ctypes.POINTER(ctypes.c_int),  # const int* A
              ctypes.POINTER(ctypes.c_int),  # const int* B
              ctypes.c_int                   # int size
          ]
          return lib

#run - teste
C_funtion= Lib_C()
C_funtion.main()
