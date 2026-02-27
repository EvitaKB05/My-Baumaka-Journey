import { Injectable } from '@nestjs/common';
import { CreateSubjectDto } from './dto/create-subject.dto';
import { UpdateSubjectDto } from './dto/update-subject.dto';
import { FileService } from 'src/file.service';
import { Subject } from './entities/subject.entity';

@Injectable()
export class SubjectsService {
  constructor(private fileService: FileService<Subject[]>) { }

  create(createSubjectDto: CreateSubjectDto) {
    const subjects = this.fileService.read();

    // для простоты новый id = текущее количество карточек + 1
    const subject = { ...createSubjectDto, id: subjects.length + 1 };

    this.fileService.add(subject);
  }

  findAll(title?: string): Subject[] {
    const subjects = this.fileService.read();

    return title
      ? subjects.filter((subject) =>
        subject.title.toLowerCase().includes(title.toLowerCase()),
      )
      : subjects;
  }

  findOne(id: number): Subject | null {
    const subjects = this.fileService.read();

    return subjects.find((subject) => subject.id === id) ?? null;
  }

  update(id: number, updateSubjectDto: UpdateSubjectDto): void {
    const subjects = this.fileService.read();

    const updatedSubjects = subjects.map((subject) =>
      subject.id === id ? { ...subject, ...updateSubjectDto } : subject,
    );

    this.fileService.write(updatedSubjects);
  }

  remove(id: number): void {
    const filteredSubjects = this.fileService
      .read()
      .filter((subject) => subject.id !== id);

    this.fileService.write(filteredSubjects);
  }
}
