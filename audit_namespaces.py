import os
import re
import sys

def get_expected_namespace(rel_path):
    # Normalize path separators to '/' for consistent splitting
    normalized_path = rel_path.replace('\\', '/')
    parts = normalized_path.split('/')
    
    # Remove filename
    parts = parts[:-1]
    
    # Filter out inc and src
    filtered_parts = [p for p in parts if p not in ('inc', 'src')]
    
    if not filtered_parts:
        return "cubiq"

    if filtered_parts[0] == 'core':
        base = ["cubiq", "common"]
        remaining = filtered_parts[1:]
        return "::".join(base + remaining)
    
    elif filtered_parts[0] == 'games':
        if len(filtered_parts) < 2:
            return "cubiq::games"
        game_name = filtered_parts[1]
        base = ["cubiq", game_name]
        remaining = filtered_parts[2:]
        return "::".join(base + remaining)
    
    elif filtered_parts[0] == 'platform':
        if len(filtered_parts) < 2:
            return "cubiq::platform"
        platform_name = filtered_parts[1]
        base = ["cubiq", "platform", platform_name]
        remaining = filtered_parts[2:]
        return "::".join(base + remaining)
    
    else:
        base = ["cubiq"]
        return "::".join(base + filtered_parts)

def strip_comments(text):
    # Remove multi-line comments /* ... */
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.DOTALL)
    # Remove single-line comments // ...
    text = re.sub(r'//.*', '', text)
    return text

def get_declared_namespaces(content):
    content = strip_comments(content)
    lines = content.splitlines()
    
    stack = []
    found_namespaces = set()
    
    for line in lines:
        line = line.strip()
        if not line: continue
        
        # Match 'namespace A::B {' or 'namespace A {'
        match = re.search(r'^namespace\s+([^\{;]+)\s*\{', line)
        if match:
            parts_str = match.group(1).strip()
            parts = [p.strip() for p in parts_str.split('::')]
            stack.append(parts)
            full_name = "::".join([p for sublist in stack for p in sublist])
            found_namespaces.add(full_name)
        elif line == '}':
            if stack:
                stack.pop()
    
    return found_namespaces

def main():
    root_dir = os.getcwd()
    mismatches = []
    extensions = ('.h', '.hpp', '.cpp', '.cc')
    
    for dirpath, dirnames, filenames in os.walk(root_dir):
        # Skip build directories
        if 'build' in dirpath.split(os.sep):
            continue
            
        for filename in filenames:
            if filename.endswith(extensions):
                full_path = os.path.join(dirpath, filename)
                rel_path = os.path.relpath(full_path, root_dir)
                
                expected = get_expected_namespace(rel_path)
                
                try:
                    with open(full_path, 'r', encoding='utf-8') as f:
                        content = f.read()
                    
                    declared = get_declared_namespaces(content)
                    
                    # Check if expected is in declared or vice versa? 
                    # Usually we want the top-level namespace to match.
                    # If there are multiple, all should ideally be within the expected hierarchy.
                    # But for this audit, let's check if 'expected' is one of the declared namespaces.
                    if expected not in declared:
                        mismatches.append({
                            'path': rel_path,
                            'declared': list(declared) if declared else ["None"],
                            'expected': expected
                        })
                except Exception as e:
                    print(f"Error reading {rel_path}: {e}")

    if not mismatches:
        print("No mismatches found.")
    else:
        print(f"{'File Path':<60} | {'Declared Namespace(s)':<40} | {'Expected Namespace'}")
        print("-" * 130)
        for m in mismatches:
            declared_str = ", ".join(m['declared'])
            print(f"{m['path']:<60} | {declared_str:<40} | {m['expected']}")

if __name__ == "__main__":
    main()
