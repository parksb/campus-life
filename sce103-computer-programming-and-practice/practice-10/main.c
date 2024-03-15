#include <stdio.h>

struct employee {
  int entry_year;
  char name[20];
  char residence[20];
};

struct employee get_employee();
void print_employee(struct employee e);
int employee_equal(struct employee e1, struct employee e2);
void swap(struct employee *el, struct employee *e2);

int main() {
  struct employee emp1, emp2;

  emp1 = get_employee();
  emp2 = get_employee();

  if (employee_equal(emp1, emp2)) {
    printf("employees are equal\n");
  } else {
    printf("employees are not equal\n");
  }

  printf("swap before: \n");
  print_employee(emp1);
  print_employee(emp2);

  swap(&emp1, &emp2);

  printf("swap after: \n");
  print_employee(emp1);
  print_employee(emp2);

  return 0;
}

struct employee get_employee() {
  int entry_year;
  char name[20];
  char residence[20];

  printf("entry name, residence, entry_year for first employee: ");
  scanf("%s %s %d", name, residence, &entry_year);

  struct employee e;
  e.entry_year = entry_year;
  strcpy(e.name, name);
  strcpy(e.residence, residence);

  return e;
}

void print_employee(struct employee e) {
  printf("name: %s, residence: %s, entry_year: %d\n", e.name, e.residence, e.entry_year);
}

int employee_equal(struct employee e1, struct employee e2) {
  return (e1.entry_year == e2.entry_year) && (strcmp(e1.name, e2.name) == 0) && (strcmp(e1.residence, e2.residence) == 0);
}

void swap(struct employee *el, struct employee *e2) {
  struct employee temp = *el;
  *el = *e2;
  *e2 = temp;
}
