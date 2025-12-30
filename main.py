import os
import sys

# Convert "4.euler" -> "Euler"
def format_name(name):
    parts = name.split("-")
    return "".join(p[:1].upper() + p[1:] for p in parts if p)

# Remove numeric prefix: "4.euler" -> "euler"
def remove_number(name):
    return name[name.index(".") + 1:]

def print_preamble():
    print(r"""\documentclass[12pt]{article}

\usepackage[a4paper,portrait]{geometry}
\geometry{top=2.5cm,bottom=0.5cm,left=0.5cm,right=0.5cm,columnsep=1cm}

\usepackage{multicol}
\setlength{\columnseprule}{0.2pt}

\usepackage{fancyhdr}
\usepackage{lastpage}

\pagestyle{fancy}
\fancyhf{}
\lhead{IIT Guwahati (Akansh, Shreyans, Tanmay)}
\rhead{\thepage\ of \pageref{LastPage}}

\usepackage{microtype}
\usepackage{xcolor}

\usepackage[
    cachedir=minted-cache,
    cache=true
]{minted}
\setminted{
    breaklines,
    fontsize=\footnotesize,
    tabsize=2
}

          
\setlength{\parindent}{0pt}
\usemintedstyle{bw}

\newcommand{\includecpp}[2]{
    \subsection{#1}
    \inputminted[
        breaklines,
        fontsize=\footnotesize,
        frame=single,
        framesep=1pt,
        tabsize=2,
        rulecolor=\color{black}
    ]{cpp}{#2}
}

\begin{document}
\thispagestyle{fancy}
\pagenumbering{Roman}

% \begin{center}
%     {\Huge \textsc{ICPC Team Reference Document}}\\[2em]
%     {\LARGE \textbf{Kaaju Kishmish}}\\[1em]
%     {\Large Akansh Khandelwal \quad • \quad Shreyans Garg \quad • \quad Tanmay Mittal}\\[2em]
%     \rule{\textwidth}{1pt}
% \end{center}

\pagenumbering{arabic}
\vspace{1em}

\begin{multicols}{2}
""")


def print_postamble():
    print(r"""
\end{multicols}

\end{document}
""")
    
def latex_escape(text):
    return text.replace("_", r"\_")

def main():
    include_cmds = {
        ".cpp": r"\includecpp",
    }

    source_path = os.path.join(os.getcwd(), "src")

    print_preamble()

    for dirname in sorted(os.listdir(source_path)):
        dirpath = os.path.join(source_path, dirname)
        if not os.path.isdir(dirpath):
            continue

        section_name = latex_escape(format_name(remove_number(dirname)))
        print(r"\section{{{}}}".format(section_name))

        for file in sorted(os.listdir(dirpath)):
            filepath = os.path.join(dirpath, file)
            if not os.path.isfile(filepath):
                continue

            filename, ext = os.path.splitext(file)
            if ext not in include_cmds:
                sys.stderr.write(f"Skipping unsupported file {filepath}\n")
                continue

            subsection_name = latex_escape(format_name(remove_number(filename)))
            relpath = f"src/{dirname}/{file}"

            print(f"{include_cmds[ext]}{{{subsection_name}}}{{{relpath}}}")

        print()  # blank line between sections

    print_postamble()

if __name__ == "__main__":
    main()
