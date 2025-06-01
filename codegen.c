#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

void generate_function_declaration(ASTNode* node);

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

// Helper to emit function prototypes
void emit_function_prototypes(ASTNode* decl) {
    if (!decl) return;
    if (decl->type == NODE_SEQUENCE) {
        emit_function_prototypes(decl->data.sequence.first);
        emit_function_prototypes(decl->data.sequence.second);
    } else if (decl->type == NODE_FUNCTION_DECLARATION && strcmp(decl->data.func_decl.name, "main") != 0) {
        fprintf(output_file, "double %s(", decl->data.func_decl.name);
        Parameter* param = decl->data.func_decl.parameters;
        int first = 1;
        while (param) {
            if (!first) fprintf(output_file, ", ");
            fprintf(output_file, "double %s", param->name);
            param = param->next;
            first = 0;
        }
        fprintf(output_file, ");\n");
    }
}

void emit_function_definitions(ASTNode* decl) {
    if (!decl) return;
    if (decl->type == NODE_SEQUENCE) {
        emit_function_definitions(decl->data.sequence.first);
        emit_function_definitions(decl->data.sequence.second);
    } else if (decl->type == NODE_FUNCTION_DECLARATION && strcmp(decl->data.func_decl.name, "main") != 0) {
        generate_function_declaration(decl);
    }
}

// Helper: emit number-to-string conversion
static void emit_number_to_string_expr(ASTNode* node) {
    fprintf(output_file, "num_to_str(");
    generate_code(node);
    fprintf(output_file, ")");
}

// Helper: emit string expression (handles string, number, or concatenation)
static void emit_string_expr(ASTNode* node) {
    if (node->type == NODE_STRING) {
        fprintf(output_file, "\"%s\"", node->data.string_value);
    } else if (node->type == NODE_NUMBER) {
        emit_number_to_string_expr(node);
    } else if (node->type == NODE_IDENTIFIER) {
        fprintf(output_file, "num_to_str(");
        generate_code(node);
        fprintf(output_file, ")");
    } else if (node->type == NODE_BINARY_OP && node->data.binary_op.op == OP_ADD) {
        fprintf(output_file, "str_concat(");
        emit_string_expr(node->data.binary_op.left);
        fprintf(output_file, ", ");
        emit_string_expr(node->data.binary_op.right);
        fprintf(output_file, ")");
    } else {
        generate_code(node);
    }
}

// At the top of generate_program, emit helper functions
void generate_program(ASTNode* node) {
    fprintf(output_file, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\n");
    // Helper for number to string
    fprintf(output_file, "char* num_to_str(double n) { char buf[32]; snprintf(buf, sizeof(buf), \"%%g\", n); return strdup(buf); }\n");
    // Helper for string concatenation
    fprintf(output_file, "char* str_concat(const char* a, const char* b) { size_t l1 = strlen(a), l2 = strlen(b); char* r = malloc(l1+l2+1); strcpy(r,a); strcat(r,b); return r; }\n\n");
    // Emit function prototypes
    if (node->type == NODE_PROGRAM) {
        emit_function_prototypes(node->data.program.declarations);
    }
    // Emit all non-main function definitions
    if (node->type == NODE_PROGRAM) {
        emit_function_definitions(node->data.program.declarations);
    }
    // Generate main function
    fprintf(output_file, "int main() {\n");
    if (node->type == NODE_PROGRAM && node->data.program.main_function) {
        // Emit the body of the LazyUi main function here
        generate_code(node->data.program.main_function->data.func_decl.body);
    }
    fprintf(output_file, "    return 0;\n}\n");
}

void generate_function_declaration(ASTNode* node) {
    // Only generate non-main functions
    if (strcmp(node->data.func_decl.name, "main") == 0) {
        return;
    }
    
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
    if (node->data.binary_op.op == OP_ADD &&
        (node->data.binary_op.left->type == NODE_STRING || node->data.binary_op.right->type == NODE_STRING ||
         node->data.binary_op.left->type == NODE_BINARY_OP || node->data.binary_op.right->type == NODE_BINARY_OP)) {
        emit_string_expr(node);
    } else {
        fprintf(output_file, "(");
        generate_code(node->data.binary_op.left);
        switch (node->data.binary_op.op) {
            case OP_ADD: fprintf(output_file, " + "); break;
            case OP_SUB: fprintf(output_file, " - "); break;
            case OP_MUL: fprintf(output_file, " * "); break;
            case OP_DIV: fprintf(output_file, " / "); break;
            case OP_GT: fprintf(output_file, " > "); break;
            case OP_LT: fprintf(output_file, " < "); break;
            case OP_EQ: fprintf(output_file, " == "); break;
            case OP_NEQ: fprintf(output_file, " != "); break;
            case OP_GTE: fprintf(output_file, " >= "); break;
            case OP_LTE: fprintf(output_file, " <= "); break;
            default: fprintf(output_file, " ? "); break;
        }
        generate_code(node->data.binary_op.right);
        fprintf(output_file, ")");
    }
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
    // If the expression is a string or a string concatenation, use %s
    if (node->data.print_stmt.expression->type == NODE_STRING ||
        (node->data.print_stmt.expression->type == NODE_BINARY_OP &&
         node->data.print_stmt.expression->data.binary_op.op == OP_ADD)) {
        fprintf(output_file, "    printf(\"%%s\\n\", ");
        emit_string_expr(node->data.print_stmt.expression);
        fprintf(output_file, ");\n");
    } else {
        fprintf(output_file, "    printf(\"%%f\\n\", ");
        generate_code(node->data.print_stmt.expression);
        fprintf(output_file, ");\n");
    }
}

void generate_if(ASTNode* node) {
    fprintf(output_file, "    if (");
    generate_code(node->data.if_stmt.condition);
    fprintf(output_file, ") {\n");
    generate_code(node->data.if_stmt.then_branch);
    fprintf(output_file, "    }");
    
    if (node->data.if_stmt.else_branch) {
        fprintf(output_file, " else {\n");
        generate_code(node->data.if_stmt.else_branch);
        fprintf(output_file, "    }");
    }
    fprintf(output_file, "\n");
}

void generate_while(ASTNode* node) {
    fprintf(output_file, "    while (");
    generate_code(node->data.while_stmt.condition);
    fprintf(output_file, ") {\n");
    generate_code(node->data.while_stmt.body);
    fprintf(output_file, "    }\n");
}

void generate_for(ASTNode* node) {
    fprintf(output_file, "    ");
    generate_code(node->data.for_stmt.init);
    fprintf(output_file, "    while (");
    generate_code(node->data.for_stmt.condition);
    fprintf(output_file, ") {\n");
    generate_code(node->data.for_stmt.body);
    fprintf(output_file, "        ");
    generate_code(node->data.for_stmt.update);
    fprintf(output_file, "    }\n");
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
        case NODE_IF:
            generate_if(node);
            break;
        case NODE_WHILE:
            generate_while(node);
            break;
        case NODE_FOR:
            generate_for(node);
            break;
        case NODE_STRING:
            fprintf(output_file, "\"%s\"", node->data.string_value);
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