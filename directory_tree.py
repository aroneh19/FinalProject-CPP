import os

def list_files(startpath, print_output=True, return_output=False, exclude_dirs=None):
    """
    List all files and directories in the specified path in a tree-like format.
    
    Args:
        startpath (str): The directory path to start listing from
        print_output (bool): Whether to print the tree structure to console
        return_output (bool): Whether to return the tree structure as a string
        exclude_dirs (list): List of directory names to exclude (e.g. ['.git', 'node_modules'])
        
    Returns:
        str: The directory tree as a string (if return_output is True)
    """
    if exclude_dirs is None:
        exclude_dirs = []
        
    if not os.path.exists(startpath):
        error_msg = f"Error: The path '{startpath}' does not exist."
        if print_output:
            print(error_msg)
        if return_output:
            return error_msg
        return
        
    output = []
    
    for root, dirs, files in os.walk(startpath):
        # Skip excluded directories
        dirs[:] = [d for d in dirs if d not in exclude_dirs]
        
        level = root.replace(startpath, '').count(os.sep)
        indent = ' ' * 4 * level
        folder_line = f"{indent}{os.path.basename(root)}/"
        if print_output:
            print(folder_line)
        if return_output:
            output.append(folder_line)
            
        subindent = ' ' * 4 * (level + 1)
        for f in files:
            file_line = f"{subindent}{f}"
            if print_output:
                print(file_line)
            if return_output:
                output.append(file_line)
                
    if return_output:
        return '\n'.join(output)

# Example usage:
if __name__ == "__main__":
    # Replace with an actual path or use input to get it
    path = "."  # Current directory
    # Common directories to exclude
    exclude = ['.git', '__pycache__', 'node_modules', '.venv', 'venv', '.vscode']
    list_files(path, exclude_dirs=exclude)