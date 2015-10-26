/*
 * Copyright [2012-2015] DaSE@ECNU
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ./sql_parser/ast_node/ast_expr_node.h
 *  Created on: May 22, 2015 11:36:17 AM
 *      Author: fzh
 *       Email: fzhedu@gmail.com
 *
 * Description:
 *   Those classes in this file are used to describe the calculation tree of
 * expression, just store some main information. so don't match the class used
 * to describe the calculation tree of execution completely.
 */
/*
 * those classes in this file are used to describe the calculation tree of
 * expression,
 * just store some main information, so don't match the class used to describe
 * the
 * calculation tree of execution completely.
 */

#ifndef SQL_PARSER_AST_NODE_AST_EXPR_NODE_H_
#define SQL_PARSER_AST_NODE_AST_EXPR_NODE_H_
#include <set>
#include <string>
#include "../ast_node/ast_node.h"
using std::string;
using std::set;
/**
 * @brief The AST of const expression.
 * @details AstExprConst mainly includes expression type and type name.
 */
class AstExprConst : public AstNode {
 public:
  AstExprConst(AstNodeType ast_node_type, string expr_type, string data);
  ~AstExprConst();
  void Print(int level = 0) const;
  ErrorNo SemanticAnalisys(SemanticContext* sem_cnxt);
  void RecoverExprName(string& name);
  void ReplaceAggregation(AstNode*& agg_column, set<AstNode*>& agg_node,
                          bool is_select);
  string expr_type_;
  string data_;
};
/**
 * @brief The AST of unary expression.
 * @details AstExprUnary mainly includes expression type and content.
 * The member AstNode* arg0_ stands for a expression or a number.
 */
class AstExprUnary : public AstNode {
 public:
  AstExprUnary(AstNodeType ast_node_type, string expr_type, AstNode* arg0);
  ~AstExprUnary();
  void Print(int level = 0) const;
  ErrorNo SemanticAnalisys(SemanticContext* sem_cnxt);
  void RecoverExprName(string& name);
  void ReplaceAggregation(AstNode*& agg_column, set<AstNode*>& agg_node,
                          bool is_select);
  AstNode* arg0_;
  string expr_type_;
};
/**
 * @brief The AST of expression function.
 */
class AstExprFunc : public AstNode {
 public:
  AstExprFunc(AstNodeType ast_node_type, string expr_type, AstNode* arg0,
              AstNode* arg1, AstNode* arg2);
  ~AstExprFunc();
  void Print(int level = 0) const;
  ErrorNo SemanticAnalisys(SemanticContext* sem_cnxt);
  void RecoverExprName(string& name);
  void ReplaceAggregation(AstNode*& agg_column, set<AstNode*>& agg_node,
                          bool is_select);

  AstNode* arg0_;
  AstNode* arg1_;
  AstNode* arg2_;
  string expr_type_;
};
/**
 * @brief The AST of binary calculation expression.
 */
class AstExprCalBinary : public AstNode {
 public:
  AstExprCalBinary(AstNodeType ast_node_type, string expr_type, AstNode* arg0,
                   AstNode* arg1);
  ~AstExprCalBinary();
  void Print(int level = 0) const;
  ErrorNo SemanticAnalisys(SemanticContext* sem_cnxt);
  void RecoverExprName(string& name);
  void ReplaceAggregation(AstNode*& agg_column, set<AstNode*>& agg_node,
                          bool is_select);
  AstNode* arg0_;
  AstNode* arg1_;
  string expr_type_;
};
/**
 * @brief The AST of binary compare expression.
 */
class AstExprCmpBinary : public AstNode {
 public:
  AstExprCmpBinary(AstNodeType ast_node_type, string expr_type, AstNode* arg0,
                   AstNode* arg1);
  AstExprCmpBinary(AstNodeType ast_node_type, string cmp_para, int cmp_type,
                   AstNode* arg0, AstNode* arg1);

  ~AstExprCmpBinary();
  void Print(int level = 0) const;
  ErrorNo SemanticAnalisys(SemanticContext* sem_cnxt);
  void RecoverExprName(string& name);
  void ReplaceAggregation(AstNode*& agg_column, set<AstNode*>& agg_node,
                          bool is_select);
  AstNode* arg0_;
  AstNode* arg1_;
  string expr_type_;

  string cmp_para_;  //  "ALL","ANY","SOME","NULL","SUBQUERY"
};
/**
 * @biref The AST of expression list.
 */
class AstExprList : public AstNode {
 public:
  AstExprList(AstNodeType ast_node_type, AstNode* expr, AstNode* next);
  ~AstExprList();
  void Print(int level = 0) const;
  ErrorNo SemanticAnalisys(SemanticContext* sem_cnxt);
  void RecoverExprName(string& name);
  void ReplaceAggregation(AstNode*& agg_column, set<AstNode*>& agg_node,
                          bool is_select);
  AstNode* expr_;
  AstNode* next_;
};

#endif  // SQL_PARSER_AST_NODE_AST_EXPR_NODE_H_
