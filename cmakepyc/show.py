import tkinter as tk
from tkinter import filedialog, ttk
import subprocess
import json

class ShowAddApp:
    def __init__(self, root):
        self.root = root
        self.root.title("求加法")
        self.root.geometry("550x200")

        ttk.Label(text="num a").pack(side=tk.LEFT, padx=5)
        self.add_enter_a = tk.StringVar()
        add_a = ttk.Entry(textvariable=self.add_enter_a,width=5)
        add_a.pack(side=tk.LEFT, padx=5, fill=tk.X, expand=True)

        ttk.Label(text="num b").pack(side=tk.LEFT, padx=5)
        self.add_enter_b = tk.StringVar()
        add_b = ttk.Entry(textvariable=self.add_enter_b,width=5)
        add_b.pack(side=tk.LEFT, padx=5, fill=tk.X, expand=True)

        self.browse_btn = ttk.Button(text="相加", command=self.get_add_res)
        self.browse_btn.pack(side=tk.LEFT, padx=5)

        ttk.Label(text="相加结果").pack(side=tk.LEFT, padx=5)
        #self.sum_res_num = tk.StringVar()#?
        #sum_res = ttk.Entry(textvariable=self.sum_res_num,width=10)
        #sum_res.pack(side=tk.LEFT, padx=5, fill=tk.X, expand=True)

    def get_add_res(self):
        numA = self.add_enter_a.get()
        numB = self.add_enter_b.get()
        if not numA:
            tk.messagebox.showwarning("警告", "请输入A")
            return
        
        if not numB:
            tk.messagebox.showwarning("警告", "请输入B")
            return
        
        #self.sum_res_num = 0
        #mylist = ["./sum_res", numA, numB]

        try:
            result = subprocess.run(
                ["./sum_res", numA, numB],#?
                capture_output=True,#?
                text=True,#?
                check=True
            )
            res_num = result.stdout
            #print(res_num)
            #self.sum_res_num = res_num
            ttk.Label(text=res_num).pack(side=tk.LEFT, padx=5)
        except subprocess.CalledProcessError as e:
            tk.messagebox.showerror("错误1",f"C++程序执行失败: {e.stderr}")
        except Exception as e:
            tk.messagebox.showerror("错误2",f"发生未知错误：{str(e)}")

if __name__ == "__main__":
    root = tk.Tk()
    app = ShowAddApp(root)
    root.mainloop()