
import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="GameSolver",
    version="0.1.0",
    author="Hank Meng",
    author_email="ymenghank@gmail.com",
    description="Fast two player zero-sum game solver.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/ymenghank/GameSolver",
    
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License"
    ],

    packages=setuptools.find_packages(),
    package_data={'GameSolver': ['GameSolver.dll', 'libGameSolver.so']},
)
