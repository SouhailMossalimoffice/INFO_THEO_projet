#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol_table.h"

void generate_function_declaration(ASTNode* node);

void generate_code(ASTNode* node);

static FILE* output_file;
extern SymbolTable* symbol_table;  // Declare external symbol table

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

void generate_program(ASTNode* node) {
    fprintf(output_file, "#include <stdio.h>\n\n");
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
    if (node->data.var_decl.type == TYPE_LISTA) {
        fprintf(output_file, "    double* %s = NULL;\n", node->data.var_decl.name);
        if (node->data.var_decl.initializer) {
            fprintf(output_file, "    %s = malloc(sizeof(double) * 1);\n", node->data.var_decl.name);
            fprintf(output_file, "    %s[0] = 0;\n", node->data.var_decl.name);
        }
    } else if (node->data.var_decl.type == TYPE_JADWAL) {
        fprintf(output_file, "    struct {\n");
        fprintf(output_file, "        double age;\n");
        fprintf(output_file, "        double height;\n");
        fprintf(output_file, "    } %s = {", node->data.var_decl.name);
        
        if (node->data.var_decl.initializer) {
            ASTNode* field = node->data.var_decl.initializer;
            int first = 1;
            while (field) {
                if (field->type == NODE_SEQUENCE) {
                    if (!first) fprintf(output_file, ", ");
                    generate_code(field->data.sequence.first->data.assignment.value);
                    field = field->data.sequence.second;
                    first = 0;
                } else {
                    if (!first) fprintf(output_file, ", ");
                    generate_code(field->data.assignment.value);
                    break;
                }
            }
        } else {
            fprintf(output_file, "0, 0");
        }
        fprintf(output_file, "};\n");
    } else {
        fprintf(output_file, "    double %s = ", node->data.var_decl.name);
        if (node->data.var_decl.initializer) {
            generate_code(node->data.var_decl.initializer);
        } else {
            fprintf(output_file, "0");
        }
        fprintf(output_file, ";\n");
    }
}

void generate_assignment(ASTNode* node) {
    fprintf(output_file, "    ");
    generate_code(node->data.assignment.target);
    fprintf(output_file, " = ");
    generate_code(node->data.assignment.value);
    fprintf(output_file, ";\n");
}

void generate_identifier(ASTNode* node) {
    // Just print the identifier name, no _try_error logic
    fprintf(output_file, "%s", node->data.identifier);
}

void generate_binary_op(ASTNode* node) {
    fprintf(output_file, "(");
    generate_code(node->data.binary_op.left);
    switch (node->data.binary_op.op) {
        case OP_ADD: fprintf(output_file, " + "); break;
        case OP_SUB: fprintf(output_file, " - "); break;
        case OP_MUL: fprintf(output_file, " * "); break;
        case OP_DIV: fprintf(output_file, " / "); break;
        case OP_EQ: fprintf(output_file, " == "); break;
        case OP_NEQ: fprintf(output_file, " != "); break;
        case OP_GT: fprintf(output_file, " > "); break;
        case OP_LT: fprintf(output_file, " < "); break;
        case OP_GTE: fprintf(output_file, " >= "); break;
        case OP_LTE: fprintf(output_file, " <= "); break;
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
    if (node->data.print_stmt.expression->type == NODE_STRING) {
        fprintf(output_file, "    printf(\"%s\\n\");\n", node->data.print_stmt.expression->data.string_value);
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
    if (node->data.if_stmt.else_branch) {
        fprintf(output_file, "    } else {\n");
        generate_code(node->data.if_stmt.else_branch);
    }
    fprintf(output_file, "    }\n");
}

void generate_while(ASTNode* node) {
    fprintf(output_file, "    while (");
    generate_code(node->data.while_stmt.condition);
    fprintf(output_file, ") {\n");
    generate_code(node->data.while_stmt.body);
    fprintf(output_file, "    }\n");
}

void generate_for(ASTNode* node) {
    fprintf(output_file, "    for (");
    // For initialization, we need to handle it as a statement
    if (node->data.for_stmt.init) {
        if (node->data.for_stmt.init->type == NODE_ASSIGNMENT) {
            // For assignments, we need to remove the newline and semicolon
            fprintf(output_file, "    ");
            generate_code(node->data.for_stmt.init->data.assignment.target);
            fprintf(output_file, " = ");
            generate_code(node->data.for_stmt.init->data.assignment.value);
        } else {
            generate_code(node->data.for_stmt.init);
        }
    }
    fprintf(output_file, "; ");
    
    // Condition
    generate_code(node->data.for_stmt.condition);
    fprintf(output_file, "; ");
    
    // For update, we need to handle it as a statement
    if (node->data.for_stmt.update) {
        if (node->data.for_stmt.update->type == NODE_ASSIGNMENT) {
            // For assignments, we need to remove the newline and semicolon
            generate_code(node->data.for_stmt.update->data.assignment.target);
            fprintf(output_file, " = ");
            generate_code(node->data.for_stmt.update->data.assignment.value);
        } else {
            generate_code(node->data.for_stmt.update);
        }
    }
    
    fprintf(output_file, ") {\n");
    generate_code(node->data.for_stmt.body);
    fprintf(output_file, "    }\n");
}

void generate_sequence(ASTNode* node) {
    if (node->data.sequence.first) {
        generate_code(node->data.sequence.first);
    }
    if (node->data.sequence.second) {
        generate_code(node->data.sequence.second);
    }
}

void generate_try(ASTNode* node) {
    fprintf(output_file, "    {\n");  // Outer scope for the entire try-catch
    fprintf(output_file, "        int _try_error = 0;\n");
    fprintf(output_file, "        {\n");  // Scope for try block
    generate_code(node->data.try_stmt.try_block);
    fprintf(output_file, "        }\n");
    fprintf(output_file, "        if (_try_error) {\n");  // Scope for catch block
    generate_code(node->data.try_stmt.catch_block);
    fprintf(output_file, "        }\n");
    fprintf(output_file, "    }\n");
}

void generate_array_access(ASTNode* node) {
    // Just generate array access, no _try_error logic
    fprintf(output_file, "%s[(int)(", node->data.array_access.array->data.identifier);
    generate_code(node->data.array_access.index);
    fprintf(output_file, ")]" );
}

void generate_field_access(ASTNode* node) {
    generate_code(node->data.field_access.object);
    fprintf(output_file, ".%s", node->data.field_access.field_name);
}

void generate_code(ASTNode* node) {
    if (node == NULL) return;

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
        case NODE_NUMBER:
            fprintf(output_file, "%f", node->data.number_value);
            break;
        case NODE_STRING:
            fprintf(output_file, "\"%s\"", node->data.string_value);
            break;
        case NODE_IDENTIFIER:
            generate_identifier(node);
            break;
        case NODE_FUNCTION_CALL:
            generate_function_call(node);
            break;
        case NODE_PRINT:
            generate_print(node);
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
        case NODE_SEQUENCE:
            generate_sequence(node);
            break;
        case NODE_TRY:
            generate_try(node);
            break;
        case NODE_ARRAY_ACCESS:
            generate_array_access(node);
            break;
        case NODE_FIELD_ACCESS:
            generate_field_access(node);
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