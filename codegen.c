#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

void generate_code(ASTNode* node);

static FILE* output_file;

void init_codegen(const char* output_filename) {
    output_file = fopen(output_filename, "w");
    if (!output_file) {
        fprintf(stderr, "Error: Cannot open output file %s\n", output_filename);
        exit(1);
    }
}

void close_codegen() {
    if (output_file) {
        fclose(output_file);
    }
}

void generate_program(ASTNode* node) {
    fprintf(output_file, "#include <stdio.h>\n\n");
    
    // Generate function declarations
    if (node->type == NODE_PROGRAM) {
        ASTNode *decl = node->data.program.declarations;
        while (decl) {
            if (decl->type == NODE_SEQUENCE) {
                generate_code(decl->data.sequence.first);
                decl = decl->data.sequence.second;
            } else {
                generate_code(decl);
                break;
            }
        }
    }
    
    // Generate main function
    fprintf(output_file, "int main() {\n");
    if (node->type == NODE_PROGRAM && node->data.program.main_function) {
        generate_code(node->data.program.main_function);
    }
    fprintf(output_file, "    return 0;\n}\n");
}

void generate_function_declaration(ASTNode* node) {
    fprintf(output_file, "double %s(", node->data.func_decl.name);
    
    // Generate parameters
    Parameter* param = node->data.func_decl.parameters;
    while (param) {
        fprintf(output_file, "double %s", param->name);
        param = param->next;
        if (param) fprintf(output_file, ", ");
    }
    
    fprintf(output_file, ") {\n");
    generate_code(node->data.func_decl.body);
    fprintf(output_file, "}\n\n");
}

void generate_return(ASTNode* node) {
    fprintf(output_file, "    return ");
    generate_code(node->data.return_stmt.value);
    fprintf(output_file, ";\n");
}

void generate_variable_declaration(ASTNode* node) {
    fprintf(output_file, "    double %s = ", node->data.var_decl.name);
    if (node->data.var_decl.initializer) {
        generate_code(node->data.var_decl.initializer);
    } else {
        fprintf(output_file, "0");
    }
    fprintf(output_file, ";\n");
}

void generate_assignment(ASTNode* node) {
    fprintf(output_file, "    ");
    generate_code(node->data.assignment.target);
    fprintf(output_file, " = ");
    generate_code(node->data.assignment.value);
    fprintf(output_file, ";\n");
}

void generate_binary_op(ASTNode* node) {
    fprintf(output_file, "(");
    generate_code(node->data.binary_op.left);
    
    switch (node->data.binary_op.op) {
        case OP_ADD: fprintf(output_file, " + "); break;
        case OP_SUB: fprintf(output_file, " - "); break;
        case OP_MUL: fprintf(output_file, " * "); break;
        case OP_DIV: fprintf(output_file, " / "); break;
        default: fprintf(output_file, " ? "); break;
    }
    
    generate_code(node->data.binary_op.right);
    fprintf(output_file, ")");
}

void generate_function_call(ASTNode* node) {
    fprintf(output_file, "%s(", node->data.func_call.name);
    
    // Arguments as sequence node
    if (node->data.func_call.arguments && node->data.func_call.arg_count > 0) {
        for (int i = 0; i < node->data.func_call.arg_count; i++) {
            if (i > 0) fprintf(output_file, ", ");
            generate_code(node->data.func_call.arguments[i]);
        }
    }
    
    fprintf(output_file, ")");
}

void generate_print(ASTNode* node) {
    fprintf(output_file, "    printf(\"%%f\\n\", ");
    generate_code(node->data.print_stmt.expression);
    fprintf(output_file, ");\n");
}

void generate_code(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAM:
            generate_program(node);
            break;
        case NODE_FUNCTION_DECLARATION:
            generate_function_declaration(node);
            break;
        case NODE_RETURN:
            generate_return(node);
            break;
        case NODE_VAR_DECLARATION:
            generate_variable_declaration(node);
            break;
        case NODE_ASSIGNMENT:
            generate_assignment(node);
            break;
        case NODE_BINARY_OP:
            generate_binary_op(node);
            break;
        case NODE_FUNCTION_CALL:
            generate_function_call(node);
            break;
        case NODE_PRINT:
            generate_print(node);
            break;
        case NODE_NUMBER:
            fprintf(output_file, "%f", node->data.number_value);
            break;
        case NODE_IDENTIFIER:
            fprintf(output_file, "%s", node->data.identifier);
            break;
        case NODE_SEQUENCE:
            generate_code(node->data.sequence.first);
            generate_code(node->data.sequence.second);
            break;
        default:
            fprintf(stderr, "Error: Unknown node type in code generation\n");
            break;
    }
}

void generate_code_entry(ASTNode* ast_root) {
    init_codegen("output.c");
    generate_code(ast_root);
    close_codegen();
} 